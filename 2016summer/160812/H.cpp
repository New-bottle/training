#include<cstdio>
#include<queue>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int N = 100010;
int to[N], nxt[N], head[N], cnt;
void ins(int x, int y){
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
}

int n, a[N], fa[N], md[N], md2[N], size[N], dfs_clock, st[N], ed[N];
int pos[N];

void dfs(int x){
	size[x] = 1;
	st[x] = ++dfs_clock;
	pos[dfs_clock] = x;
	for(int i = head[x]; i; i = nxt[i]) {
		dfs(to[i]);
		size[x] += size[to[i]];
	}
	ed[x] = dfs_clock;
}

struct node{
	int l, r, cnt;
}t[N * 30];
int rt[N], tot;
#define mid ((l + r) >> 1)
void update(int &o, int l, int r, int pos) {
	t[++ tot] = t[o]; o = tot; ++ t[o].cnt;
	if (l == r) return;
	if (pos <= mid) update(t[o].l, l, mid, pos);
	else update(t[o].r, mid + 1, r, pos);
}

int query(int i, int j, int rank) {
	i = rt[i], j = rt[j];
	int l = 1, r = 100000;
	while(l != r){
		if (t[t[j].l].cnt - t[t[i].l].cnt >= rank)
			r = mid, i = t[i].l, j = t[j].l;
		else {
			rank -= t[t[j].l].cnt - t[t[i].l].cnt;
			l = mid + 1, i = t[i].r, j = t[j].r;
		}
	}
	return l;
}
#undef mid

LL v[N];
inline void add(int x, LL y){
	for(;x; x -= x & (-x)) v[x] += y;
}
inline LL sum(int x){
	LL r = 0;
	for(; x <= 100000; x += x & (-x)) r += v[x];
	return r;
}
LL ans = 0;
void getans(int x){
	add(md[x], md2[x] - md[x]);
	ans = max(ans, sum(md[x]));
	for(int i = head[x]; i; i = nxt[i]) getans(to[i]);
	add(md[x], md[x] - md2[x]);
}

int main(){
	while(scanf("%d", &n) == 1){
		memset(head, 0, sizeof head); cnt = 0;
		LL sum = 0;
		for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
		for(int i = 2; i <= n; i ++) {
			scanf("%d", &fa[i]);
			ins(fa[i], i);
		}
		dfs_clock = 0;
		dfs(1);
		memset(rt, 0, sizeof rt);
		memset(t, 0, sizeof t); tot = 0;
//		update(rt[0], 1, 100000, 100000);
		for(int i = 1; i <= n; i ++) {
			rt[i] = rt[i - 1];
			update(rt[i], 1, 100000, a[pos[i]]);
		}
		for(int i = 1; i <= n; i ++) {
			md[i] = query(st[i] - 1, ed[i], (size[i] + 1) / 2);
			if (size[i] == 1) md2[i] = 100000;
			else md2[i] = query(st[i] - 1, ed[i], (size[i] + 1) / 2 + 1);
			sum += md[i];
		}
		ans = 0;
		getans(1);
		cout << sum + ans << endl;
	}
	return 0;
}
