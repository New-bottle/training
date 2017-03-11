#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1010;
typedef long long LL;

const LL INF = 1e18;
int n, d, c, t[N];

LL f[N][N];
//f[i][j] = now is ith, delayed last j's

int main()
{
	scanf("%d%d%d", &n, &d, &c);
	for (int i = 1; i <= n; ++i) scanf("%d", &t[i]);
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j <= n; ++j) f[i][j] = INF;
	f[0][0] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int k = 0; k <= i - 1; ++k)
			f[i][0] = min(f[i][0], f[i - 1][k] + 1LL * c * k * (t[i] - t[i - 1]) + d);
		for (int j = 1; j <= i; ++j) {
			f[i][j] = min(f[i][j], f[i - 1][j - 1] + 1LL * c * (j - 1) * (t[i] - t[i - 1]));
		}
	}
	cout << f[n][0] << endl;
	return 0;
}
