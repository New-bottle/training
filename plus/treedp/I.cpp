#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int P = 1e9 + 7;
int Pow(int a, int b){
	int r = 1;
	while(b) {
		if (b & 1) r = 1LL * r * a % P;
		a = 1LL * a * a % P;
		b >>= 1;
	}
	return r;
}
const int N = 200010;
int to[N << 1], nxt[N << 1], head[N], cnt;
void add(int x, int y) {
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
	to[++ cnt] = x; nxt[cnt] = head[y]; head[y] = cnt;
}
int t[N << 1], nt[N << 1], hd[N], cnt2;
void ins(int x, int y) {
	t[++ cnt2] = y; nt[cnt2] = hd[x]; hd[x] = cnt2;
//	t[++ cnt2] = x; nt[cnt2] = hd[y]; hd[y] = cnt2;
}

int dfn[N], low[N], dfs_clock, belong[N], pos[N];
void dfs(int x, int fa){
	dfn[x] = low[x] = ++ dfs_clock;
	for(int i = head[x]; i; i = nxt[i])
		if (!dfn[to[i]]) {
			dfs(to[i], x);
			low[x] = min(low[x], low[to[i]]);
		} else if (to[i] != fa) low[x] = min(low[x], dfn[to[i]]);
	if (dfn[x] == low[x]) pos[low[x]] = x;
}

int fa[N][20], n, m, size[N], num[N];
bool yes[N];
void rebuild() {
	for(int x = 1; x <= n; x ++)
		num[low[x]] ++;
	
	for(int x = 1; x <= n; x ++)
		for(int i = head[x]; i; i = nxt[i])
			if (low[x] != low[to[i]])
				ins(pos[low[x]], pos[low[to[i]]]);
	for(int x = 1; x <= n; x ++)
		if (num[x] > 1) {
			size[pos[x]] = 1;
			yes[pos[x]] = 1;
		}
//	for(int i = 1; i <= n; i ++) printf("size[%d] = %d\n", i, size[i]);
}

int sum[N], dep[N];
void getans(int x) {
	for(int i = 1; (1 << i) <= dep[x]; i ++) 
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for(int i = hd[x]; i; i = nt[i])
		if (t[i] != fa[x][0]) {
			fa[t[i]][0] = x;
			dep[t[i]] = dep[x] + 1;
			size[t[i]] += size[x];
			getans(t[i]);
		}
}
int LCA(int x, int y) {
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
	for(int i = 1; i <= m; i ++) {
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	dfs(1, -1);
//	for(int i = 1; i <= n; i ++) printf("%d %d\n", dfn[i], low[i]);
	rebuild();
	getans(1);
//	for(int i = 1; i <= 2 * n; i ++) printf("size[%d] = %d\n", i, size[i]);
	int k;
	scanf("%d", &k);
	for(int i = 1; i <= k; i ++) {
		int x, y, lca;
		scanf("%d%d" ,&x, &y);
		x = pos[low[x]]; y = pos[low[y]];
		if (x == y) {
			puts("2");
			continue;
		}
		lca = LCA(x, y);
//		printf("x = %d y = %d lca = %d\n", x, y, lca);
//		printf("%d\n", size[x] + size[y] - size[lca]);
		printf("%d\n", Pow(2, size[x] + size[y] - size[lca] * 2 + yes[lca]));
	}
	return 0;
}

