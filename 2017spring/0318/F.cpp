#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const double eps = 1e-10;
const int N = 100010;

int x[3], y[3], vx[3], vy[3];

inline double sqr(double x){ return x * x;}

int main()
{
	scanf("%d%d%d%d", &x[1], &y[1], &x[2], &y[2]);
	scanf("%d%d%d%d", &vx[1], &vy[1], &vx[2], &vy[2]);
	x[1] -= x[2];
	y[1] -= y[2];
	vx[1] -= vx[2];
	vy[1] -= vy[2];

	double ans = 0;
	if (x[1] * vx[1] + y[1] * vy[1] < 0)
		ans = (x[1] * vy[1] - y[1] * vx[1]) / sqrt(sqr(vx[1]) + sqr(vy[1]));
	else 
		ans = sqrt(sqr(x[1]) + sqr(y[1]));
	printf("%.10f\n", fabs(ans));
	return 0;
}
