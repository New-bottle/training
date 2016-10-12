#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
//#define debug

const int N = 2010, M = 100010;

struct edge{
	int x, y, w, who;
	void read() { scanf("%d%d%d", &x, &y, &w); }
	bool operator < (const edge &b) const {
		return w < b.w;
	}
}e[M];

struct LCT {
	int c[N][2], fa[N], v[N], mx[N];
	bool rev[N];
	int st[N], top;
#define L c[x][0]
#define R c[x][1]
	void init() {
		memset(c, 0, sizeof c);
		memset(fa, 0, sizeof fa);
		memset(v, 0, sizeof v);
		memset(mx, 0, sizeof mx);
		memset(rev, 0, sizeof rev);
	}
	void Push_up(int x) {
		mx[x] = x;
		if (v[mx[L]] > v[mx[x]]) mx[x] = mx[L];
		if (v[mx[R]] > v[mx[x]]) mx[x] = mx[R];
	}
	void Push_down(int x) {
		if (rev[x]) rev[x] = 0, rev[L] ^= 1, rev[R] ^= 1, swap(L, R);
	}
	bool not_root(int x) {
		return c[fa[x]][0] == x || c[fa[x]][1] == x;
	}
	void Rotate(int x) {
		int y = fa[x], z = fa[y], l = c[y][1] == x, r = l ^ 1;
		if (not_root(y)) c[z][c[z][1] == y] = x;
		fa[x] = z; fa[y] = x; fa[c[x][r]] = y;
		c[y][l] = c[x][r]; c[x][r] = y;
		Push_up(y);
	}
	void preview(int x) {
		top = 0; st[++top] = x;
		for(; not_root(x); x = fa[x])
			st[++top] = fa[x];
		for(int i = top; i; i --) Push_down(st[i]);
	}
	void splay(int x) {
		int y = 0;
		for(preview(x); not_root(x); Rotate(x))
			not_root(y = fa[x]) ? Rotate((c[y][1] == x ^ c[fa[y]][1] == y ? x : y)), 1 : 1;
		Push_up(x);
	}
	void access(int x, int las = 0) {
		for(; x; splay(x), c[x][1] = las, las = x, x = fa[x]);
	}
	void makeroot(int x) {
		access(x), splay(x), rev[x] ^= 1;
	}
	void link(int x, int y) {
		makeroot(x), fa[x] = y;
	}
	void cut(int x, int y) {
		makeroot(x), access(y), splay(y);
		if (c[y][0] == x) c[y][0] = fa[x] = 0;
	}
	int query(int x, int y) {
		makeroot(x), access(y), splay(y);
		return mx[y];
	}
}t;

struct node {
	int sum, l, r;
};
namespace segtree {
	node T[M * 30];
	int rt[M], tot;
	void update(int &o, int l, int r, int pos, int v) {
		T[++tot] = T[o], o = tot, T[o].sum += v;
		if (l == r) return;
		int mid = (l + r) >> 1;
		if (pos <= mid) update(T[o].l, l, mid, pos, v);
		else update(T[o].r, mid + 1, r, pos, v);
	}
	int query(int i, int j, int l, int r, int ql, int qr) {
		if (ql <= l && qr >= r) return T[j].sum - T[i].sum;
		int mid = (l + r) >> 1, ans = 0;
		if (ql <= mid) ans += query(T[i].l, T[j].l, l, mid, ql, qr);
		if (qr >  mid) ans += query(T[i].r, T[j].r, mid + 1, r, ql, qr);
		return ans;
	}
}

int n, m, fa[N], root[N], v[M], cnt;
int getfa(int x) {return fa[x] == x ? x : fa[x] = getfa(fa[x]);}

void ready() {
	sort(v + 1, v + m + 1);
//	cnt = m;
	cnt = unique(v + 1, v + m + 1) - v - 1;
	for(int i = 1; i <= m; i ++) 
		e[i].w = lower_bound(v + 1, v + cnt + 1, e[i].w) - v;
	sort(e + 1, e + m + 1);

	for(int i = 1; i <= m; i ++) {
		t.v[n + i] = e[i].w;
		t.mx[n + i] = n + i;
	}
	for(int i = 1; i <= n; i ++) fa[i] = i;

	for(int i = m; i; i --) {
		int f1 = getfa(e[i].x), f2 = getfa(e[i].y);
		if (f1 != f2) {
			fa[f1] = f2;
			t.link(e[i].x, n + i); t.link(e[i].y, n + i);
		} else {
			int tmp = t.query(e[i].x, e[i].y);
			t.cut(e[tmp - n].x, tmp); t.cut(e[tmp - n].y, tmp);
			t.link(e[i].x, i + n); t.link(e[i].y, i + n);
			e[tmp - n].who = i;
		}
	}

	using namespace segtree;
	for(int i = 1; i <= m; i ++) {
		rt[i] = rt[i - 1];
		update(rt[i], 0, cnt, e[e[i].who].w, v[e[i].w]);
	}
}

void init() {
	t.init();
	memset(e, 0, sizeof e);
	cnt = 0;
	using namespace segtree;
	tot = 0;
	memset(T, 0, sizeof T);
	memset(rt, 0, sizeof rt);
}

int main(){
	int T;
	scanf("%d", &T);
	while(T --) {
		init();
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= m; i ++) {
			e[i].read();
			v[i] = e[i].w;
		}
		ready();

		int q, ans = 0;
		scanf("%d", &q);
		for(int i = 1; i <= q; i ++) {
			int l, r;
			scanf("%d%d", &l, &r);
			l -= ans; r -= ans;
			for(int i = 1; i <= m; i ++) v[i] = e[i].w;
			l = lower_bound(v + 1, v + m + 1, l) - v;
			r = upper_bound(v + 1, v + m + 1, r) - v - 1;

			using namespace segtree;
			printf("%d\n", ans = query(rt[l - 1], rt[r], 0, cnt, 0, l - 1));
		}
	}
	return 0;
}
