#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 200010;
typedef long long LL;

LL t[N << 2], add[N << 2];
#define L (o << 1)
#define R (o << 1 | 1)
#define mid ((l + r) >> 1)
#define lch L, l, mid
#define rch R, mid + 1, r
void Push_up(int o) {
	t[o] = max(t[L], t[R]);
}
void Push_down(int o) {
	if (add[o]) {
		t[L] += add[o]; add[L] += add[o];
		t[R] += add[o]; add[R] += add[o];
		add[o] = 0;
	}
}
void update(int o, int l, int r, int ql, int qr, LL v) {
//	printf("update %d %d %d %d %d %lld\n", o, l, r, ql, qr, v);
	if (ql <= l && qr >= r) t[o] += v, add[o] += v;
	else {
		Push_down(o);
		if (ql <= mid) update(lch, ql, qr, v);
		if (qr >  mid) update(rch, ql, qr, v);
		Push_up(o);
	}
}
LL query(int o, int l, int r, int ql, int qr) {
	if (ql <= l && qr >= r) return t[o];
	else {
		Push_down(o);
		LL ans = 0;
		if (ql <= mid) ans = max(ans, query(lch, ql, qr));
		if (qr >  mid) ans = max(ans, query(rch, ql, qr));
		return ans;
	}
}
void print(int o, int l, int r) {
	printf("%d (%d, %d) max = %lld add = %lld\n", o, l, r, t[o], add[o]);
	if (l == r) return;
	print(lch); print(rch);
}

struct race {
	int l, r, v;
	void read() {
		scanf("%d%d%d", &l, &r, &v);
	}
}r[N];
vector<int>have[N];
int n, m, cost[N];

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &cost[i]);
	for(int i = 1; i <= m; i ++)
		r[i].read();
	for(int i = 1; i <= m; i ++)
		have[r[i].r].push_back(i);
//	update(1, 0, n, 1, n, (LL)-1e18);
	for(int i = 1; i <= n; i ++) {
		LL dp0 = query(1, 0, n, 0, i - 1);
		update(1, 0, n, i, i, dp0);
		update(1, 0, n, 0, i - 1, - cost[i]);
		for(int j = 0; j < have[i].size(); j ++)
			update(1, 0, n, 0, r[have[i][j]].l - 1, r[have[i][j]].v);
//		print(1, 0, n);
	}
	printf("%lld\n", query(1, 0, n, 0, n));
	return 0;
}
