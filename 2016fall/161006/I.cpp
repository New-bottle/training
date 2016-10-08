#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
//#define debug

typedef long long LL;
const int N = 100010;

struct node {
	int l, r, id;
	LL tmp, v;
	void read() {
		scanf("%d%d%lld", &l, &r, &v);
	}
	bool operator < (const node &b) const {
		return v < b.v || (v == b.v && id < b.id);
	}
}c[N], q[N];
bool part(const node &a) {return a.tmp < a.v;}

int v[N << 2], n, m, Q, cnt;

struct seg {
	LL sum, add;
	int len;
}t[N << 4];
#define L (o << 1)
#define R (o << 1 | 1)
#define mid ((l + r) >> 1)
#define lch L, l, mid
#define rch R, mid + 1, r
void Push_up(int o) {
	t[o].sum = t[L].sum + t[R].sum;
}
void build(int o, int l, int r) {
	if (l == r) {
		t[o].sum = t[o].add = 0;
		t[o].len = v[r] - v[l - 1];
		return;
	}
	build(lch); build(rch);
	t[o].len = t[L].len + t[R].len;
	Push_up(o);
}
void change(int o, LL v) {
	t[o].add += v;
	t[o].sum += (LL)v * t[o].len;
}
void Push_down(int o) {
	if (t[o].add) {
		change(L, t[o].add);
		change(R, t[o].add);
		t[o].add = 0;
	}
}
void update(int o, int l, int r, int ql, int qr, LL v) {
	if (ql <= l && qr >= r) change(o, v);
	else {
		Push_down(o);
		if (ql <= mid) update(lch, ql, qr, v);
		if (qr >  mid) update(rch, ql, qr, v);
		Push_up(o);
	}
}
LL query(int o, int l, int r, int ql, int qr) {
	if (ql <= l && qr >= r) return t[o].sum;
	else {
		Push_down(o);
		LL ans = 0;
		if (ql <= mid) ans += query(lch, ql, qr);
		if (qr >  mid) ans += query(rch, ql, qr);
		return ans;
	}
}
void print(int o, int l, int r) {
	printf("%2d (%d, %d) %lld %lld %d\n", o, l, r, t[o].sum, t[o].add, t[o].len);
	if (l == r) return;
	print(lch); print(rch);
}
#undef mid

int ans[N];
void solve(int ql, int qr, int l, int r) {
	if (ql > qr || l > r) return;
	if (l == r) {
		for(int i = ql; i <= qr; i ++) ans[q[i].id] = c[l].v;
		return;
	}

	int mid = (l + r) >> 1;
	for(int i = l; i <= mid; i ++)
		update(1, 1, cnt, c[i].l + 1, c[i].r, 1);
#ifdef debug
	printf("solve %d %d %d %d\n", ql, qr, l, r);
	print(1, 1, cnt);
#endif
	for(int i = ql; i <= qr; i ++)
		q[i].tmp = query(1, 1, cnt, q[i].l + 1, q[i].r);
	int qm = stable_partition(q + ql, q + qr + 1, part) - q - 1;
#ifdef debug
	for(int i = ql; i <= qr; i ++) printf("%d %d %lld %lld\n", q[i].l, q[i].r, q[i].v, q[i].tmp);
#endif
	solve(ql, qm, mid + 1, r);
	for(int i = l; i <= mid; i ++)
		update(1, 1, cnt, c[i].l + 1, c[i].r, -1);
//	for(int i = qm + 1; i <= qr; i ++) q[i].v -= q[i].tmp;
	solve(qm + 1, qr, l, mid);
}

int main(){
	scanf("%d%d%d", &n, &m, &Q);
	for(int i = 1; i <= m; i ++) c[i].read(), c[i].id = i;
	for(int i = 1; i <= Q; i ++) q[i].read(), q[i].id = i;
	for(int i = 1; i <= m; i ++) 
		v[++cnt] = c[i].l - 1,
		v[++cnt] = c[i].r;
	for(int i = 1; i <= Q; i ++)
		v[++cnt] = q[i].l - 1,
		v[++cnt] = q[i].r;
	sort(v + 1, v + cnt + 1);
	cnt = unique(v + 1, v + cnt + 1) - v - 1;
//	for(int i = 1; i <= cnt; i ++) printf("%d ", v[i]); puts("");
	for(int i = 1; i <= m; i ++) {
		c[i].l = lower_bound(v + 1, v + cnt + 1, c[i].l - 1) - v;
		c[i].r = lower_bound(v + 1, v + cnt + 1, c[i].r) - v;
	}
	for(int i = 1; i <= Q; i ++) {
		q[i].l = lower_bound(v + 1, v + cnt + 1, q[i].l - 1) - v;
		q[i].r = lower_bound(v + 1, v + cnt + 1, q[i].r) - v;
	}
	sort(c + 1, c + m + 1);
//	sort(q + 1, q + Q + 1);
//	for(int i = 1; i <= m; i ++) printf("%d %d %d\n", c[i].l, c[i].r, c[i].v);

	build(1, 1, cnt);
	solve(1, Q, 1, m);
	for(int i = 1; i <= Q; i ++)
		printf("%d\n", ans[i]);
	return 0;
}
