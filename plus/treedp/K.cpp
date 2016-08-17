#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int N = 100010;
int to[N << 1], nxt[N << 1], head[N], cnt;
void add(int x, int y) {
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
	to[++ cnt] = x; nxt[cnt] = head[y]; head[y] = cnt;
}

int n, m, fa[N][20], dep[N];
LL f[N], g[N], size[N];

void dfs(int x) {
	size[x] = 1;
	for(int i = 1; (1 << i) <= dep[x]; i ++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for(int i = head[x]; i; i = nxt[i])
		if (to[i] != fa[x][0]) {
			fa[to[i]][0] = x;
			dep[to[i]] = dep[x] + 1;
			dfs(to[i]);
			f[x] += f[to[i]] + size[to[i]];
			size[x] += size[to[i]];
		}
}
void getans(int x) {
	for(int i = head[x]; i; i = nxt[i])
		if (to[i] != fa[x][0]) {
			g[to[i]] = f[x] + g[x] - f[to[i]] - size[to[i]] + (n - size[to[i]]);
			getans(to[i]);
		}
}
int LCA(int x, int y){
	if (dep[x] < dep[y]) swap(x, y);
	int t = dep[x] - dep[y];
	for(int i = 0; i <= 19; i ++)
		if (t >> i & 1) x = fa[x][i];
	for(int i = 19; i >= 0; i --)
		if (fa[x][i] != fa[y][i])
			x = fa[x][i], y = fa[y][i];
	if (x == y) return x;
	return fa[x][0];
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; i ++) {
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	dfs(1);
	getans(1);
//	for(int i = 1; i <= n; i ++) printf("f[%d] = %d g[%d] = %d\n", i, f[i], i, g[i]); 
	for(int i = 1; i <= m; i ++) {
		int x, y, lca, t, del;
		scanf("%d%d", &x, &y);
		lca = LCA(x, y);
		double ans = 0.0;
		if (x == lca) {
			t = y;
			del = dep[y] - dep[x] - 1;
			for(int i = 0; i <= 19; i ++)
				if (del >> i & 1) t = fa[t][i];
			ans = 1.0 * ((g[x] + f[x] - f[t] - size[t]) * size[y] + f[y] * (n - size[t])) / double(size[y] * (n - size[t]));
		} else if (y == lca) {
			swap(x, y);
			t = y;
			del = dep[y] - dep[x] - 1;
			for(int i = 0; i <= 19; i ++)
				if (del >> i & 1) t = fa[t][i];
			ans = 1.0 * ((g[x] + f[x] - f[t] - size[t]) * size[y] + f[y] * (n - size[t])) / double(size[y] * (n - size[t]));
//			ans = 1.0 * (g[x] + f[y] + f[x] - f[t] - size[t]) / double(size[y] * (n - size[t]));
		} else {
			ans = 1.0 * (f[x] * size[y] + f[y] * size[x]) / double(size[x] * size[y]);
		}
//		printf("x = %d y = %d lca = %d\n", x, y, lca);
		ans += dep[x] + dep[y] - 2 * dep[lca] + 1.0;
		printf("%.7lf\n", ans);
	}
	return 0;
}
