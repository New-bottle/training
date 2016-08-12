#pragma GCC optimize("Ofast")
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>

typedef long double ldb;
typedef long long lli;

const ldb eps0 = 1e-16;

const int N = 5000;
int n;

struct Point {
	lli x, y;
	Point operator - (const Point& r) const {
		Point ans;
		ans.x = x - r.x;
		ans.y = y - r.y;
		return ans;
	}
	ldb angle;
} pt[N], sorted[N], base;

inline lli cross(const Point& a, const Point& b)
{
	return a.x * b.y - a.y * b.x;
}

inline lli dot(const Point& a, const Point& b)
{
	return a.x * b.x + a.y * b.y;
}

inline bool acute(int i, int j)
{
	auto a = sorted[i] - base;
	auto b = sorted[j] - base;
	//std::cout << dot(a, b) << ' ' << cross(a, b) << std::endl;
	return dot(a, b) > 0 && cross(a, b) >= 0;
}

inline bool zeroang(int i, int j)
{
	return cross(sorted[i] - base, sorted[j] - base) == 0;
}

ldb getangle(const Point& a)
{
	long long ra2 = a.x * a.x + a.y * a.y;
	ldb evala = std::acos(a.x / std::sqrt(ra2));
	if (a.y < 0)
		evala = 2 * 3.141592653589793238462643383279 - evala;
	evala += eps0;
	return evala;
}

long long nac, nzero;

void work2()
{
	int i = 0, j = 1, cnt = 1;
	bool warped = false;
	while (1) {
#ifdef SFDEB
		//std::cout << "START " << i << ' ' << j << std::endl;
		std::cout << i << ' ' << j << std::endl;
#endif
		while (i != j && acute(i, j)) {
			if (warped && zeroang(i, j))
				break;
			//std::cout << "INC" << std::endl;
			++cnt;
			++j;
			if (j == n - 1) { warped = true; j = 0; }
		}
		nac += cnt - 1;
		//std::cout << "ADD " << cnt - 1 << ' ' << nac << std::endl;
		++i;
		//std::cout << "FINI  " << i << ' ' << j << std::endl;
		if (i == n - 1)
			break;
		if (i == j) {
			++j;
			++cnt;
			if (j == n - 1) { warped = true; j = 0; }
		}
		--cnt;
	}
	i = 0; j = 1; cnt = 1;
	while (1) {
		j = i + 1;
		cnt = 1;
		while (j != n - 1 && zeroang(i, j)) {
			++cnt;
			++j;
		}
		nzero += cnt * (cnt - 1) / 2;
		i = j;
		if (i == n - 1)
			break;
	}
}

void work()
{
	nac = nzero = 0;
	for (int i = 0; i < n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		pt[i] = {x, y, 0};
	}
	for (int i = 0; i < n; ++i) {
		std::memcpy(sorted, pt, n * sizeof(sorted[0]));
		std::swap(sorted[n - 1], sorted[i]);
		base = sorted[n - 1];
		for (int i = 0; i < n; ++i)
			sorted[i].angle = getangle(sorted[i] - base);
		std::sort(sorted, sorted + n - 1, [](const Point& a, const Point& b){
			//return cross(a - base, b - base) < 0;
			//return getangle(a - base) < getangle(b - base);
			return a.angle < b.angle;
		});
		//std::cout << "BASE " << base.x << ' ' << base.y << std::endl;
		//for (int j = 0; j < n - 1; ++j)
			//std::cout << j << ' ' << sorted[j].x << ' ' << sorted[j].y << std::endl;
		work2();
	}
	long long ttl = (long long) n * (n - 1) * (n - 2) / 2;
	long long fans = ttl - nac;
	//std::cout << "RESULT " << nac << ' ' << nzero << ' ' << ttl << std::endl;
	std::cout << ttl / 3 - fans << std::endl;
}

int main()
{
	while (~scanf("%d", &n)) {
		work();
	}
	return 0;
}
