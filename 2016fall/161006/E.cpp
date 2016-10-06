#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int INF = 1e9;
const int N = 200010, M = 200010;
int to[N << 1], nxt[N << 1], head[N], cnt, len[N << 1];
void add(int x, int y, int z) {
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt; len[cnt] = z;
	to[++ cnt] = x; nxt[cnt] = head[y]; head[y] = cnt; len[cnt] = z;
}

struct edge {
	int x, y, w, id;
	bool operator < (const edge &b) const {
		return w < b.w;
	}
	void read() {
		scanf("%d%d%d", &x, &y, &w);
	}
}e[M];
bool used[M], vis[N];
int fa[N], dfn[N], n, m, dfs_clock;
int getfa(int x) {return fa[x] == x ? fa[x] : fa[x] = getfa(fa[x]);}
LL ans[M];

int dep[N], top[N], son[N], size[N];
void dfs(int x) {
	size[x] = 1; son[x] = 0;
	for(int i = head[x]; i; i = nxt[i])
		if (!size[to[i]]) {
			fa[to[i]] = x;
			dep[to[i]] = dep[x] + 1;
			dfs(to[i]);
			size[x] += size[to[i]];
			if (size[to[i]] > size[son[x]]) son[x] = to[i];
		}
}
void Connect(int x, int f) {
//	printf("Connect %d %d\n", x, f);
	dfn[x] = ++dfs_clock;
	top[x] = f;
	if (son[x]) Connect(son[x], f);

	for(int i = head[x]; i; i = nxt[i])
		if (to[i] != fa[x] && to[i] != son[x])
			Connect(to[i], to[i]);
}

#define L (o << 1)
#define R (o << 1 | 1)
#define mid ((l + r) >> 1)
#define lch L, l, mid
#define rch R, mid + 1, r
int t[N << 2];
void build(int o, int l, int r) {
	if (l == r) {
		t[o] = INF;
		return;
	}
	build(lch);
	build(rch);
	t[o] = INF;
}
void update(int o, int l, int r, int ql, int qr, int v) {
	if (ql > qr) return;
	if (ql <= l && qr >= r) {
		t[o] = min(t[o], v);
	} else {
		if (ql <= mid) update(lch, ql, qr, v);
		if (qr >  mid) update(rch, ql, qr, v);
	}
}
int getans(int o, int l, int r, int pos) {
	if (l == r) return t[o];
	int ans = t[o];
	if (pos <= mid) ans = min(ans, getans(lch, pos));
	else ans = min(ans, getans(rch, pos));
	return ans;
}
void modify(int x, int y, int v) {
	while(top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		update(1, 1, n, dfn[top[x]], dfn[x], v);
		x = fa[top[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	update(1, 1, n, dfn[son[x]], dfn[y], v);
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i ++) {
		e[i].read();
		e[i].id = i;
	}
	sort(e + 1, e + m + 1);
	
	for(int i = 1; i <= n; i ++) fa[i] = i;
	LL sum = 0;
	for(int i = 1; i <= m; i ++) {
		int x = e[i].x, y = e[i].y,
			f1 = getfa(x), f2 = getfa(y);
		if (f1 != f2) {
			sum += e[i].w;
			fa[f1] = f2;
			used[i] = 1;
			add(x, y, e[i].w);
		}
	}
//	printf("sum = %lld\n", sum);
//	for(int i = 1; i <= m; i ++) printf("%d %d %d %d\n", e[i].x, e[i].y, e[i].w, used[i]);
	for(int i = 1; i <= n; i ++) fa[i] = 0;
	dfs(1);
	Connect(1, 1);
	
	build(1, 1, n);
	for(int i = 1; i <= m; i ++) if (!used[i]) {
		modify(e[i].x, e[i].y, e[i].w);
	}
	for(int i = 1; i <= m; i ++) {
		if (!used[i]) ans[e[i].id] = sum;
		else {
			int x = e[i].x, y = e[i].y;
			if (dep[x] < dep[y]) swap(x, y);
			int v = getans(1, 1, n, dfn[x]);
			if (v == INF) ans[e[i].id] = -1;
			else ans[e[i].id] = sum - e[i].w + v;
		}
	}
	for(int i = 1; i <= m; i ++) printf("%lld\n", ans[i]);
	return 0;
}
//w = 0
