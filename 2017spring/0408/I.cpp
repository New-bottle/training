#include <cstdio>
#include <queue>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 110, M = N * N;
typedef long long LL;

int to[M << 1], nxt[M << 1], head[N], cnt;
LL len[M << 1];
void ins(int x, int y, LL z) 
{
	to[++cnt] = y; nxt[cnt] = head[x]; head[x] = cnt; len[cnt] = z;
}
void add(int x, int y, LL z)
{
	ins(x, y, z);
	ins(y, x, z);
}

int n, m, x[N], y[N], p[N];

LL d[N], mp[N][N];
bool inq[N];
inline LL sqr(LL x){return x * x;}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i <= n + 1; ++i) 
			for (int j = 0; j <= n + 1; ++j) mp[i][j] = 1e18;
		for (int i = 1; i <= n; ++i)
			scanf("%d%d%d", &x[i], &y[i], &p[i]);
		scanf("%d%d", &x[0], &y[0]);
		scanf("%d%d", &x[n + 1], &y[n + 1]);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (sqr(x[i] - x[j]) + sqr(y[i] - y[j]) <= sqr(p[i])) {
					mp[i][j] = min(mp[i][j], 2LL);
				}
		for (int i = 0; i <= n + 1; ++i)
			for (int j = 0; j <= n + 1; ++j)
				if (i != j) {
					mp[i][j] = min(mp[i][j], abs((LL)x[i] - x[j]) + abs((LL)y[i] - y[j]));
//					ins(i, j, abs((LL)x[i] - x[j]) + abs((LL)y[i] - y[j]));
				}
		for (int k = 0; k <= n + 1; ++k)
			for (int i = 0; i <= n + 1; ++i)
				for (int j = 0; j <= n + 1; ++j)
					mp[i][j] = min(mp[i][j], mp[i][k] + mp[k][j]);
		cout << mp[0][n + 1] << endl;
	}
	return 0;
}
