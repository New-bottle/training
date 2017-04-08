#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1 << 20;

int n;
double a[22][22], f[N];

int main()
{
	int T, cs = 0;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				scanf("%lf", &a[i][j]);
		memset(f, 0, sizeof f);
		f[(1 << n) - 1] = 1;
		for (int mask = (1 << n) - 1; mask; --mask)
			for (int i = 1; i <= n; ++i)
				if (mask >> (i - 1) & 1)
				for (int j = i + 1; j <= n; ++j) 
					if (mask >> (j - 1) & 1) {
						int l = __builtin_popcount(mask);
						double p = 2.0 / (l * (l - 1));
						f[mask ^ (1 << (i - 1))] += p * f[mask] * a[j][i];
						f[mask ^ (1 << (j - 1))] += p * f[mask] * a[i][j];
					}
		printf("Case %d: ", ++cs);
		for (int i = 1; i <= n; ++i)
			printf("%.6f%c", f[1 << (i - 1)], i == n ? '\n' : ' ');
	}
	return 0;
}
