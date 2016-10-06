#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

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
}t[N << 2];
#define L (o << 1)
#define R (o << 1 | 1)
#define mid ((l + r) >> 1)
#define lch L, l, mid
#define rch R, mid + 1, r
void build(int o, int 
void Push_up(int o) {
	t[o].sum = t[L].sum + t[R].sum;
}
void Push_down(int o) {
	s
}

void solve(int ql, int qr, int l, int r) {
	if (ql > qr || l > r) return;

	if (l == r) {
		for(int i = ql; i <= qr; i ++) ans[q[i].id] = c[l].v;
		return;
	}

	int mid = (l + r) >> 1;
	for(int i = l; i <= mid; i ++)
		update(1, 1, cnt, v[c[i].l + 1], v[c[i].r], 1);
	for(int i = ql; i <= qr; i ++)
		q[i].tmp = query(1, 1, cnt, q[i].l, q[i].r);
	int qm = stable_partition(q + ql, q + qr + 1, part) - q - 1;

	solve(ql, qm, mid + 1, r);
	for(int i = l; i <= mid; i ++)
		update(1, 1, cnt, v[c[i].l + 1], v[c[i].r], -1);
	for(int i = qm + 1; i <= qr; i ++) q[i].v -= q[i].tmp;
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
	cnt = unique(v + 1, v + cnt + 1) - cnt - 1;
	for(int i = 1; i <= m; i ++) {
		c[i].l = lower_bound(v + 1, v + cnt + 1, c[i].l - 1) - v;
		c[i].r = lower_bound(v + 1, v + cnt + 1, c[i].r) - v;
	}
	for(int i = 1; i <= Q; i ++) {
		q[i].l = lower_bound(v + 1, v + cnt + 1, q[i].l - 1) - v;
		q[i].r = lower_bound(v + 1, v + cnt + 1, q[i].r) - v;
	}
	sort(q + 1, q + Q + 1);

	build(1, 1, cnt);
	solve(1, Q, q, m);
	return 0;
}
