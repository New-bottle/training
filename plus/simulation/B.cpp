#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 10010;
int to[N << 1], nxt[N << 1], head[N], cnt, len[N << 1];
void add(int x, int y, int z) {
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt; len[cnt] = z;
	to[++ cnt] = x; nxt[cnt] = head[y]; head[y] = cnt; len[cnt] = z;
}

int n, dfn[N], dfs_clock, top[N], son[N], fa[N], dep[N], size[N], v[N];
void dfs(int x) {
	size[x] = 1;
	for(int i = head[x]; i; i = nxt[i])
		if (to[i] != fa[x]) {
			fa[to[i]] = x;
			dep[to[i]] = dep[x] + 1;
			v[to[i]] = len[i];
			dfs(to[i]);
			size[x] += size[to[i]];
			if (size[to[i]] > size[son[x]]) son[x] = to[i];
		}
}
void Connect(int x, int f) {
	dfn[x] = ++ dfs_clock;
	top[x] = f;
	if (son[x]) Connect(son[x], f);
	for(int i = head[x]; i; i = nxt[i])
		if (to[i] != fa[x] && to[i] != son[x])
			Connect(to[i], to[i]);
}

int t[N << 2];
#define L (o << 1)
#define R (o << 1 | 1)
#define mid ((l + r) >> 1)
#define lch L, l, mid
#define rch R, mid + 1, r
void Push_up(int o) {
	t[o] = max(t[L], t[R]);
}
void update(int o, int l, int r, int pos, int v) {
	if (l == r) t[o] = v;
	else {
		if (pos <= mid) update(lch, pos, v);
		else update(rch, pos, v);
		Push_up(o);
	}
}
int query(int o, int l, int r, int ql, int qr) {
	if (ql > qr) return 0;
	if (ql <= l && qr >= r) return t[o];
	else {
		int ans = 0;
		if (ql <= mid) ans = max(ans, query(lch, ql, qr));
		if (qr >  mid) ans = max(ans, query(rch, ql, qr));
		return ans;
	}
}
void print(int o, int l, int r) {
	printf("t[%d] (%d, %d) = %d\n", o, l, r, t[o]);
	if (l == r) return;
	print(lch); print(rch);
}

int query(int x, int y) {
	int ans = 0;
	while(top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		ans = max(ans, query(1, 1, n, dfn[top[x]], dfn[x]));
		x = fa[top[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	ans = max(ans, query(1, 1, n, dfn[son[x]], dfn[y]));
	return ans;
}

void init() {
	dfs_clock = 0;
	memset(head, 0, sizeof head); cnt = 1;
	memset(top, 0, sizeof top);
	memset(son, 0, sizeof son);
	memset(fa, 0, sizeof fa);
	memset(dep, 0, sizeof dep);
}

char opt[10];
int main(){
	int T;
	scanf("%d", &T);
	while(T --) {
		init();
		scanf("%d", &n);
		for(int i = 1; i < n; i ++) {
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			add(x, y, z);
		}
		dfs(1);
		Connect(1, 1);
		for(int i = 2; i <= n; i ++) update(1, 1, n, dfn[i], v[i]);
		for(;;) {
			scanf("%s", opt);
			if (opt[0] == 'D') break;
			int x, y;
			scanf("%d%d", &x, &y);
			if (opt[0] == 'Q') {
				printf("%d\n", query(x, y));
			}
			if (opt[0] == 'C') {
				x = (x << 1) + 1;
				int u = to[x], v = to[x ^ 1];
				if (dep[u] > dep[v]) swap(u, v);
//				printf("%d %d\n", u, v);
				update(1, 1, n, dfn[v], y);
			}
//			print(1, 1, n);
		}
	}
	return 0;
}
