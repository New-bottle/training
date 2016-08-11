#include <cmath>
#include <iomanip>
#include <iostream>
#include <cstdio>

typedef long double ldb;

int n;

void work()
{
	int t, x, y;
	int ot, ox, oy;
	scanf("%d%d%d", &ot, &ox, &oy);
	ldb ans = 0;
	for (int i = 1; i < n; ++i) {
		scanf("%d%d%d", &t, &x, &y);
		long long dx = x - ox;
		long long dy = y - oy;
		ldb dist = std::sqrt(dx * dx + dy * dy);
		ldb diff = dist / (t - ot);
		ot = t; ox = x; oy = y;
		ans = std::max(ans, diff);
	}
	std::cout << std::fixed << std::setprecision(15) << ans << std::endl;
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; ++i) {
		scanf("%d", &n);
		work();
	}
}
