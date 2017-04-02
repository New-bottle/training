#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100010, M = 200010;

int to[M << 1], nxt[M << 1], head[N], cnt, len[M << 1];
void add (int x, int y, int z) 
{
	to[++cnt] = y; nxt[cnt] = head[x]; head[x] = cnt; len[cnt] = z;
	to[++cnt] = x; nxt[cnt] = head[y]; head[y] = cnt; len[cnt] = z;
}

struct edge
{
	int x, y, w;
	bool operator < (const edge &b) const {
		return w < b.w;
	}
}e[M];

int f[N][20], d[N], g[N][20], n, m;
void dfs (int x)
{
	for (int i = 1; (1 << i) <= d[x]; ++i) {
		f[x][i] = f[f[x][i - 1]][i - 1];
		g[x][i] = max(g[x][i - 1], g[f[x][i - 1]][i - 1]);
	}
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f[x][0]) {
			f[to[i]][0] = x;
			g[to[i]][0] = len[i];
			d[to[i]] = d[x] + 1;
			dfs(to[i]);
		}
}

int query(int x, int y)
{
	if (d[x] < d[y]) swap(x, y);
	int k = d[x] - d[y];
	int ans = 0;
	for (int i = 0; i < 20; ++i)
		if ((k >> i) & 1) {
			ans = max(ans, g[x][i]);
			x = f[x][i];
		}
	if (x == y) return ans;
	for (int i = 17; i >= 0; --i)
		if (f[x][i] != f[y][i]) {
			ans = max(ans, max(g[x][i], g[y][i]));
			x = f[x][i]; y = f[y][i];
		}
	return max(ans, max(g[x][0], g[y][0]));
}
struct ques
{
	int x, y, id;
}q[M];

int fa[N];
int getfa(int x) {return x == fa[x] ? x : fa[x] = getfa(fa[x]);}
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i)
		scanf("%d%d%d", &e[i].x, &e[i].y, &e[i].w);
	sort(e + 1, e + m + 1);
	for (int i = 1; i <= n; ++i) fa[i] = i;
	for (int i = 1; i <= m; ++i) {
		int f1 = getfa(e[i].x), f2 = getfa(e[i].y);
		if (f1 != f2) {
			fa[f2] = f1;
			add(e[i].x, e[i].y, e[i].w);
		}
	}

	dfs(1);
	int Q = 0;
	scanf("%d", &Q);
	for (int i = 1; i <= Q; ++i) {
		scanf("%d%d", &q[i].x, &q[i].y);
		printf("%d\n", query(q[i].x, q[i].y));
	}
	return 0;
}
