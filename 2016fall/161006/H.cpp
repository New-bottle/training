#include <iostream>
#include <cstdlib>
#include <cmath>
#include <utility>

typedef long double ldb;
const ldb pi = 3.14159265358979323846264338327950288;

const ldb eps_dist = 1e-6;
const ldb eps_climb = 1e-9;

void panic()
{
	std::cout << "NO" << std::endl;
	std::exit(0);
}

struct Point {
	ldb x, y, z;
	Point operator + (const Point& rhs) const {
		return Point{x + rhs.x, y + rhs.y, z + rhs.z};
	}
	Point operator - () const {
		return Point{-x, -y, -z};
	}
	Point operator - (const Point& rhs) const {
		return *this + - rhs;
	}
	Point operator * (ldb m) const {
		return Point{x * m, y * m, z * m};
	}
	ldb distance(const Point& p) const {
		ldb dx = p.x - x;
		ldb dy = p.y - y;
		ldb dz = p.z - z;
		return dx * dx + dy * dy + dz * dz;
	}
	ldb distance() const {
		return x * x + y * y + z * z;
	}
	Point cross(const Point& p) const {
		ldb nx = y * p.z - p.y * z;
		ldb ny = z * p.x - p.z * x;
		ldb nz = x * p.y - p.x * y;
		return Point{nx, ny, nz};
	}
	ldb dot(const Point& p) const {
		return x * p.x + y * p.y + z * p.z;
	}
} c1, c2, u1, u2, v1, v2;
typedef Point P;

ldb getdist(P p, P c, P u, P v)
{
	P tmp = p - c, b = u.cross(v);
	return std::fabs(tmp.dot(b) / b.distance());
}

std::istream& operator >> (std::istream& is, Point& p)
{
	return is >> p.x >> p.y >> p.z;
}

std::ostream& operator << (std::ostream& os, Point& p)
{
	return os << p.x << ' ' << p.y << ' ' << p.z << std::endl;
}

ldb rand_theta()
{
	return (ldb) rand() * pi / RAND_MAX;
}

Point get_point(ldb theta, P c, P u, P v)
{
	ldb co = std::cos(theta);
	ldb si = std::sin(theta);
	return c + u * co + v * si;
}

const ldb T0 = 30;
const ldb Tmul = 0.98;
const ldb Tfini = 1e-10;
Point climb(P c1, P u1, P v1, P c2, P u2, P v2)
{
	ldb theta = rand_theta();
	Point p = get_point(theta, c1, u1, v1);
	ldb dist = getdist(p, c2, u2, v2);
	for (ldb T = T0; T > Tfini; T *= Tmul) {
		ldb dtheta = (rand_theta() - pi / 2) * T;
		ldb ntheta = theta + dtheta;
		while (ntheta < -2 * pi)
			ntheta += pi;
		while (ntheta > 2 * pi)
			ntheta -= pi;
		Point np = get_point(ntheta, c1, u1, v1);
		ldb ndist = getdist(np, c2, u2, v2);
		//std::cout << T << '\t' << ndist << '\t' << dist << std::endl;
		if (ndist < dist) {
			theta = ntheta;
			dist = ndist;
		}
	}
	p = get_point(theta, c1, u1, v1);
	if (getdist(p, c2, u2, v2) > eps_climb)
		panic();
	return p;
}

std::pair<Point, Point> get_points(P c1, P u1, P v1, P c2, P u2, P v2)
{
	Point p0 = climb(c1, u1, v1, c2, u2, v2);
	for (int i = 0; i < 1000; ++i) {
		Point p1 = climb(c1, u1, v1, c2, u2, v2);
		if (p0.distance(p1) > eps_dist)
			return {p0, p1};
	}
	panic();
	return {c1, c2};
}

bool samedir(P u1, P v1, P u2, P v2)
{
	P d1 = u1.cross(v1);
	P d2 = u2.cross(v2);
	P d3 = d1.cross(d2);
	if (d3.distance() < eps_dist)
		return true;
	else
		return false;
}

bool test_btw(std::pair<P, P> pts, std::pair<P, P> qts)
{
	bool b1 = (pts.first - qts.first).dot(pts.first - qts.second) < 0;
	bool b2 = (pts.second - qts.first).dot(pts.second - qts.second) < 0;
	return b1 ^ b2;
}

int main()
{
	srand(19961227);
	std::cin >> c1 >> u1 >> v1 >> c2 >> u2 >> v2;
	if (samedir(u1, v1, u2, v2))
		panic();
	auto pts = get_points(c1, u1, v1, c2, u2, v2);
	auto qts = get_points(c2, u2, v2, c1, u1, v1);
	//std::cout << pts.first << pts.second << std::endl;
	//std::cout << qts.first << qts.second << std::endl;
	if (test_btw(pts, qts))
		std::cout << "YES" << std::endl;
	else
		panic();
	return 0;
}
