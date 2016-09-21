#include <cmath>
#include <iomanip>
#include <iostream>

typedef long double ldb;
const ldb sqrt2 = std::sqrt((ldb) 2);
const ldb infinity = 1e18;
const ldb eps = 1e-9;

int d, n, b;

struct Obst {
	int x, h;
} obst[100];

ldb trybnc(int bnc)
{
	int segs = bnc + 1;
	//std::cout << "SEGS = " << segs << std::endl;
	ldb sdist = (ldb) d / segs;
	//std::cout << "SDIST = " << sdist << std::endl;
	ldb ans = std::sqrt(sdist);
	for (int i = 0; i < n; ++i) {
		//std::cout << "OBST " << i << std::endl;
		ldb rndcbnc = round(obst[i].x / sdist);

		ldb deltax = std::min(
				std::fabs(obst[i].x - rndcbnc * sdist), std::min(
				std::fabs(obst[i].x - (rndcbnc - 1) * sdist),
				std::fabs(obst[i].x - (rndcbnc + 1) * sdist))
		);
		//std::cout << "DELTAX = " << deltax << std::endl;
		if (deltax < eps)
			return infinity;

		//ldb t = (ldb) -1 + std::sqrt((ldb) 1 + 2 * obst[i].h);
		//ldb t = std::sqrt(2 * obst[i].h / (2 * deltax + 1));
		//ldb t = sqrt2 * std::sqrt(h - deltax)
		ldb t = std::sqrt(2 * obst[i].h / (sdist / deltax - 1));
		//std::cout << "T = " << t << std::endl;
		ldb vx = deltax / t;
		//std::cout << "VX = " << vx << std::endl;
		ldb vy = (sdist / 2 - deltax) / vx /* * g */;
		//std::cout << "VY = " << vy << std::endl;
		ldb vy02 = vy * vy + 2 * obst[i].h;
		//std::cout << "VY0 = " << std::sqrt(vy02) << std::endl;
		if (vy02 > vx * vx)
			ans = std::max(ans, std::sqrt(vy02 + vx * vx));
	}
	return ans;
}

int main()
{
	while (std::cin >> d >> n >> b) {
		for (int i = 0; i < n; ++i) {
			std::cin >> obst[i].x;
			std::cin >> obst[i].h;
		}
		ldb ans = infinity;
		for (int bnc = 0; bnc <= b; ++bnc) {
			ans = std::min(ans, trybnc(bnc));
		}
		std::cout << std::fixed << std::setprecision(10) << ans << std::endl;
	}
	return 0;
}
