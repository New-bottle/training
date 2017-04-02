#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const double eps = 1e-8;
int x[2], y[2], r[2];

typedef long long LL;
LL sqr (int x)
{
	return 1LL * x * x;
}
LL dist (int x1, int y1, int x2, int y2)
{
	return 1LL * sqr(x2 - x1) + sqr(y2 - y1);
}
int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d%d%d%d", &r[0], &x[0], &y[0], &r[1], &x[1], &y[1]);
		LL dis = dist(x[0], y[0], x[1], y[1]);
//		printf("dis = %.6f\n", sqrt(dis));
//		cout << "dis = " << sqrt(double(dis)) << endl;
		if (sqrt(dis) + r[1] < r[0] + eps) puts("Rich");
		else puts("Dead");
	}
	return 0;
}
