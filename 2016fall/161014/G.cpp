#include <cmath>
#include <iostream>

typedef long double ldb;

const ldb eps0 = 1e-9;
const ldb eps1 = 1e-7;
const ldb eps2 = 1e-5;

ldb T, v1, v2;
ldb sqrdiff;

bool work2()
{
	ldb a = -sqrdiff;
	ldb b = 1200 * v2 * v2 + 600 * v1 * v1;
	ldb c = 600 * 600 * v2 * v2 - 2 * 300 * 300 * v1 * v1;
	ldb delta = b * b - 4 * a * c;
	delta += eps0;
	if (delta < 0)
		return false;
	ldb y = (-b + std::sqrt(delta)) / (2 * a);
	if (y < -eps1 || y - eps1 >= 300)
		return false;
	//std::cout << y << std::endl;
	//ldb t = (600 + y) / v1;
	ldb t1 = (600 - y) / v1 + T;
	ldb t2 = (900 + std::sqrt(300 * 300 + y * y)) / v2;
	return t2 - eps2 < t1;
}

bool work()
{
	std::cin >> T >> v2 >> v1;
	if (v2 < eps0)
		return false;
	sqrdiff = v1 * v1 - v2 * v2;
	ldb delta = 360000 * v1 * v1 - 720000 * sqrdiff;
	ldb t, x;
	delta += eps0;
	if (delta < 0)
		return work2();

	if (std::fabs(v1 - v2) < eps0) {
		x = 0;
		t = 300 / v1;
	} else {
		t = (600 * v1 - std::sqrt(delta)) / (2 * sqrdiff);
		x = v1 * t - 300;
	}
	//std::cout << t << ' ' << x << std::endl;
	if (x - eps1 >= 300)
		return work2();
	ldb t1 = (600 - x) / v1 + T;
	ldb t2 = (600 + x) / v2;
	return t2 - eps2 < t1;
}

int main()
{
	int TT;
	std::cin >> TT;
	for (int t = 1; t <= TT; ++t) {
		std::cout << "Case #" << t << ": ";
		bool ans = work();
		std::cout << (ans ? "Yes" : "No") << std::endl;
	}
	return 0;
}
