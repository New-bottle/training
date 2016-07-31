#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 200010;
int to[N << 1], nxt[N << 1], head[N], cnt;
void add(int x, int y){
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
	to[++ cnt] = x; nxt[cnt] = head[y]; head[y] = cnt;
}

struct Rec{
	int x1, x2, y1, y2, val;
}rec[N * 10];
struct Event{
	int l, r, y, val, rank;
}events[N * 10];
bool operator < (const Event &a, const Event &b){
	return a.y < b.y || (a.y == b.y && a.rank < b.rank);
}

struct treasure{
	int key, chest, val;
}a[N];
int st[N], ed[N], n, m, dfs_clock, dep[N], fa[N][20];

int LCA(int x, int y){
	if (dep[x] < dep[y]) swap(x, y);
	int t = dep[x] - dep[y];
	for(int i = 0; i < 20; i ++) if (t >> i & 1) x = fa[x][i];
	for(int i = 19; i >= 0; i --)
		if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	if (x == y) return x;
	return fa[x][0];
}

void dfs(int x){
	st[x] = ++ dfs_clock;
	for(int i = 1; (1 << i) <= dep[x]; i ++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for(int i = head[x]; i; i = nxt[i])
		if (st[to[i]] == 0){
			dep[to[i]] = dep[x] + 1;
			fa[to[i]][0] = x;
			dfs(to[i]);
		}
	ed[x] = dfs_clock;
}

struct node{
	int tag, max;
}t[N << 3];
#define mid ((l + r) >> 1)
#define L (o << 1)
#define R (o << 1 | 1)
#define lch L, l, mid
#define rch R, mid + 1, r

void Push_up(int o){
	t[o].max = max(t[L].max, t[R].max);
}
void change(int o, int v){
	t[o].tag += v; t[o].max += v;
}
void Push_down(int o){
	if (t[o].tag){
		change(L, t[o].tag);
		change(R, t[o].tag);
		t[o].tag = 0;
	}
}
void update(int o, int l, int r, int ql, int qr, int v){
	if (ql > qr) return;
	if (ql <= l && qr >= r) change(o, v);
	else{
		Push_down(o);
		if (ql <= mid) update(lch, ql, qr, v);
		if (qr >  mid) update(rch, ql, qr, v);
		Push_up(o);
	}
}

int main(){
	int T, cs = 0;
	scanf("%d", &T);
	while(cs < T){
		printf("Case #%d: ", ++ cs);

		memset(head, 0, sizeof head);
		memset(st, 0, sizeof st);
		memset(fa, 0, sizeof fa);
		memset(dep, 0, sizeof dep);
		memset(t, 0, sizeof t);
		cnt = dfs_clock = 0;
		scanf("%d%d", &n, &m);
		int x, y;
		for(int i = 1; i < n; i ++){
			scanf("%d%d", &x, &y);
			add(x, y);
		}
		dfs(1);
//		for(int i = 1; i <= n; i ++) printf("st[%d] = %d ed[%d] = %d\n", i, st[i], i, ed[i]);
		int tot = 0, num = 0, ans = 0, tmp = 0;
		for(int i = 1; i <= m; i ++){
			scanf("%d%d%d", &a[i].key, &a[i].chest, &a[i].val);
			int lca = LCA(a[i].key, a[i].chest);
			if (a[i].key == a[i].chest){
				tmp += a[i].val;
				for(int j = head[a[i].key]; j; j = nxt[j])
					if (to[j] != fa[a[i].key][0]){
						rec[++ tot] = (Rec){st[to[j]], ed[to[j]], st[to[j]], ed[to[j]], -a[i].val};
					}
				if (1 <= st[a[i].key] - 1 && ed[a[i].key] + 1 <= n){
					rec[++ tot] = (Rec){1, st[a[i].key] - 1, ed[a[i].key] + 1, n, -a[i].val};
					rec[++ tot] = (Rec){ed[a[i].key] + 1, n, 1, st[a[i].key] - 1, -a[i].val};
				}
				if (1 <= st[a[i].key] - 1)
					rec[++ tot] = (Rec){1, st[a[i].key] - 1, 1, st[a[i].key] - 1, -a[i].val};
				if (ed[a[i].key] + 1 <= n)
					rec[++ tot] = (Rec){ed[a[i].key] + 1, n, ed[a[i].key] + 1, n, -a[i].val};
			}else if (a[i].key == lca){
				for(int j = head[a[i].key]; j; j = nxt[j])
					if (to[j] != fa[a[i].key][0] && LCA(to[j], a[i].chest) == to[j]){
						y = to[j];
						break;
					}
				if (1 <= st[y] - 1) rec[++ tot] = (Rec){1, st[y] - 1, st[a[i].chest], ed[a[i].chest], a[i].val};
				if (ed[y] + 1 <= n) rec[++ tot] = (Rec){ed[y] + 1, n, st[a[i].chest], ed[a[i].chest], a[i].val};
			}else if (a[i].chest == lca){
				for(int j = head[a[i].chest]; j; j = nxt[j])
					if (to[j] != fa[a[i].chest][0] && LCA(to[j], a[i].key) == to[j]){
						y = to[j];
						break;
					}
				if (1 <= st[y] - 1) rec[++ tot] = (Rec){st[a[i].key], ed[a[i].key], 1, st[y] - 1, a[i].val};
				if (ed[y] + 1 <= n) rec[++ tot] = (Rec){st[a[i].key], ed[a[i].key], ed[y] + 1, n, a[i].val};
			}else{
				rec[++ tot] = (Rec){st[a[i].key], ed[a[i].key], st[a[i].chest], ed[a[i].chest], a[i].val};
			}
//			if (rec[tot].x1 == 0) printf("%d %d %d lca = %d\n", a[i].key, a[i].chest, a[i].val, lca);
		}
//		for(int i = 1; i <= tot; i ++)
//			printf("%d %d %d %d %d\n", rec[i].x1, rec[i].x2, rec[i].y1, rec[i].y2, rec[i].val);
		int tt = 0;
		for(int i = 1; i <= tot; i ++){
//			if (rec[i].x1 == 0 && rec[i].x2 == 0) printf("%d\n", ++ tt);
			events[++ num] = (Event){rec[i].x1, rec[i].x2, rec[i].y1, rec[i].val, 1};
			events[++ num] = (Event){rec[i].x1, rec[i].x2, rec[i].y2 + 1, -rec[i].val, 0};
		}
		sort(events + 1, events + num + 1);
		for(int i = 1; i <= num; i ++){
			if (events[i].y > events[i - 1].y || i == 1) ans = max(ans, t[1].max);
			update(1, 1, n, events[i].l, events[i].r, events[i].val);
			if (i == num) ans = max(ans, t[1].max);
//			printf("%d\n", t[1].max);
		}
		printf("%d\n", ans + tmp);
	}
	return 0;
}
