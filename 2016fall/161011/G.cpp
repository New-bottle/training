#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>

typedef long long lli;
typedef long double ldb;

const ldb eps = 1e-7;

struct Point {
	lli x, y;
	ldb angle;
	bool operator < (const Point& rhs) const {
		return angle < rhs.angle;
	}
} pts[500];

void work()
{
	int n;
	std::cin >> n;
	long long sx = 0, sy = 0;
	for (int i = 0; i < n; ++i) {
		std::cin >> pts[i].x >> pts[i].y;
		sx += pts[i].x;
		sy += pts[i].y;
	}
	ldb cx = (ldb) sx / n;
	ldb cy = (ldb) sy / n;
	ldb distc = 0;
	for (int i = 0; i < n; ++i) {
		ldb dx = pts[i].x - cx;
		ldb dy = pts[i].y - cy;
		pts[i].angle = std::atan2((ldb) dx, (ldb) dy);
		ldb dc = std::sqrt(dx * dx + dy * dy);
		if (distc > eps && std::fabs(dc - distc) > eps * distc) {
			puts("NO");
			return;
		}
		distc = dc;
	}
	std::sort(pts, pts + n);
	ldb ang = 0;
	for (int i = 1; i < n; ++i) {
		ldb dangle = pts[i].angle - pts[i - 1].angle;
		if (ang > eps && std::fabs(dangle - ang) > eps * ang) {
			puts("NO");
			return;
		}
		ang = dangle;
	}
	if (std::fabs(2 * 3.141592653589793238462643383279 + pts[0].angle - pts[n - 1].angle - ang) > eps * ang) {
		puts("NO");
		return;
	}
	puts("YES");
	return;
}

int main()
{
	std::ios::sync_with_stdio(false);
	int T;
	std::cin >> T;
	while (T --> 0) {
		work();
	}
}
