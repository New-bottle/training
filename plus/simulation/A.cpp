#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;
int to[N << 1], nxt[N << 1], head[N], tot;
void add(int x, int y) {
	to[++ tot] = y; nxt[tot] = head[x]; head[x] = tot;
	to[++ tot] = x; nxt[tot] = head[y]; head[y] = tot;
}

struct node {
	int l, r, cnt;
}t[N * 40];
int root[N], cnt = 0, n, m, num;

#define mid ((l + r) >> 1)
void update(int &o, int l, int r, int pos) {
	t[++cnt] = t[o]; o = cnt; ++t[o].cnt;
	if (l == r) return;
	if (pos <= mid) update(t[o].l, l, mid, pos);
	else update(t[o].r, mid + 1, r, pos);
}

int query(int i, int j, int k, int h, int rank) {
	i = root[i], j = root[j], k = root[k], h = root[h];
	int l = 1, r = num;
	while(l != r) {
		if (t[t[i].l].cnt + t[t[j].l].cnt - t[t[k].l].cnt - t[t[h].l].cnt >= rank)
			r = mid, i = t[i].l, j = t[j].l, k = t[k].l, h = t[h].l;
		else {
			rank -= t[t[i].l].cnt + t[t[j].l].cnt - t[t[k].l].cnt - t[t[h].l].cnt;
			l = mid + 1, i = t[i].r, j = t[j].r, k = t[k].r, h = t[h].r;
		}
	}
	return l;
}

int fa[N][20], dep[N], v[N], a[N];
void dfs(int x) {
	root[x] = root[fa[x][0]];
	update(root[x], 1, num, v[x]);
	for(int i = 1; (1 << i) <= dep[x]; i ++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for(int i = head[x]; i; i = nxt[i])
		if (to[i] != fa[x][0]) {
			fa[to[i]][0] = x;
			dep[to[i]] = dep[x] + 1;
			dfs(to[i]);
		}
}
int LCA(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	int t = dep[x] - dep[y];
	for(int i = 0; i < 20; i ++)
		if (t >> i & 1) x = fa[x][i];
	for(int i = 19; i >= 0; i --)
		if (fa[x][i] != fa[y][i])
			x = fa[x][i], y = fa[y][i];
	if (x == y) return x;
	return fa[x][0];
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++) {
		scanf("%d", &v[i]);
		a[i] = v[i];
	}
	sort(a + 1, a + n + 1);
	num = unique(a + 1, a + n + 1) - a - 1;
	for(int i = 1; i <= n; i ++)
		v[i] = lower_bound(a + 1, a + num + 1, v[i]) - a;
	
	for(int i = 1; i < n; i ++) {
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	dfs(1);
	for(int i = 1; i <= m; i ++) {
		int x, y, k;
		scanf("%d%d%d", &x, &y, &k);
		int lca = LCA(x, y);
		printf("%d\n", a[query(x, y, lca, fa[lca][0], k)]);
	}
	return 0;
}
