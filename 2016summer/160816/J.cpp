#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <ctime>

typedef long double ldb;

const int N = 800;

struct Point {
	ldb x, y;
} arr[N], brr[N];

const ldb inf = 1e19;
const ldb eps3 = 1e-8;
const ldb eps = 1e-6;

ldb allx[N * 2];
ldb ally[N * 2];

int n, m;

ldb dist2(const Point& a, const Point& b)
{
	ldb dx = a.x - b.x;
	ldb dy = a.y - b.y;
	return dx * dx + dy * dy;
}

ldb gr;

ldb eval(const Point& p)
{
	ldb ar = 0;
	ldb aR = inf;
	ldb br = 0;
	ldb bR = inf;
	for (int i = 0; i < n; ++i) {
		ldb dis = dist2(p, arr[i]);
		ar = std::max(ar, dis);
		bR = std::min(bR, dis);
	}
	for (int i = 0; i < m; ++i) {
		ldb dis = dist2(p, brr[i]);
		br = std::max(br, dis);
		aR = std::min(aR, dis);
	}
	ldb ans = ar - aR;
	ldb bns = br - bR;
	if (ans < bns) {
		gr = ar;
		return ans;
	} else {
		gr = br;
		return bns;
	}
#if 0
	if (ans > 0)
		ans *= 1e6;
#endif
}

int ny;

inline bool valid (ldb x)
{
	return x > -1.0000001e4 && x < 1.0000001e4;
}

Point rndp(const Point& p, ldb T)
{
	ldb dx, dy;
	do {
		dx = (ldb) rand() * T / RAND_MAX - T / 2;
		dy = (ldb) rand() * T / RAND_MAX - T / 2;
	} while (!valid(dx + p.x) || !valid(dy + p.y));
	return Point{dx + p.x, dy + p.y};
}

Point ann()
{
	ldb T = 1e7;
	ldb Tfini = 1e-8;
	ldb Tmul = 0.95;

	Point p{0, 0};
	ldb v = eval(p);

	while (T > Tfini) {
		Point np = rndp(p, T);
		ldb nv = eval(np);
		if (nv < eps) {
			p = np;
			break;
		}
		if (nv < v) {
			p = np;
			v = nv;
		} else if (std::exp((v - nv) / T * 1000) > (ldb) rand() / RAND_MAX) {
			p = np;
			v = nv;
		}
		T *= Tmul;
	}
	return p;
}


int main()
{
	srand(19961227);
	std::cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		std::cin >> arr[i].x >> arr[i].y;
		allx[i] = arr[i].x;
		ally[i] = arr[i].y;
	}
	for (int i = 0; i < m; ++i) {
		std::cin >> brr[i].x >> brr[i].y;
		allx[i + n] = brr[i].x;
		ally[i + n] = brr[i].y;
	}
	allx[n + m] = -1e-4;
	allx[n + m + 1] = 1e-4;
	ally[n + m] = -1e-4;
	ally[n + m + 1] = 1e-4;
	std::sort(allx, allx + n + m + 2);
	std::sort(ally, ally + n + m + 2);
	int nx = std::unique(allx, allx + n + m + 2) - allx;
	ny = std::unique(ally, ally + n + m + 2) - ally;


	Point p{0, 0};
	ldb v = 1e9;
	for (int i = 0; i < 100; ++i) {
		Point np = ann();
		ldb nv = eval(np);
		if (nv < v)
			p = np, v = nv;
		if (nv < eps)
			break;
	}
	v = eval(p);
	if (v < eps) {
		std::cout << "YES" << std::endl;
		std::cout
			<< std::fixed << std::setprecision(10) << p.x << ' '
			<< std::fixed << std::setprecision(10) << p.y << ' '
			<< std::fixed << std::setprecision(10) << std::sqrt(gr)  << " v = " << v << std::endl;

	} else {
		std::cout << "NO" << std::endl;
	}

	
	return 0;
}
