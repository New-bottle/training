#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1010;

int f[N][N], a[N][N], n, m;
int main()
{
	int T, cs = 0;
	scanf("%d", &T);
	while (T--) {
		printf("Case %d: ", ++cs);
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j) scanf("%d", &a[i][j]);
		f[1][1] = a[1][1];
		for (int j = 2; j <= m; ++j)
			f[1][j] = f[1][j - 1] + a[1][j];
		for (int i = 2; i <= n; ++i)
			for (int j = 1; j <= m; ++j) 
				if (j == 1) f[i][j] = f[i - 1][j] + a[i][j];
				else f[i][j] = max(f[i - 1][j], f[i][j - 1]) + a[i][j];
		printf("%d\n", f[n][m]);
	}
	return 0;
}
