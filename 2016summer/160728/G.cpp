#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int N = 40010;
int n, m;
int to[N << 1], nxt[N << 1], head[N], cnt;
bool yes[N << 1];
int t[N << 1], nt[N << 1], hd[N], cnt2;
LL len[N << 1], l[N << 1];
void add(int x, int y, int z){
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt; l[cnt] = z;
	to[++ cnt] = x; nxt[cnt] = head[y]; head[y] = cnt; l[cnt] = z;
}
void ins(int x, int y, LL z){
	t[++ cnt2] = y; nt[cnt2] = hd[x]; hd[x] = cnt2; len[cnt2] = z;
	t[++ cnt2] = x; nt[cnt2] = hd[y]; hd[y] = cnt2; len[cnt2] = z;
}

int dfn[N], low[N], dfs_clock, fa[N], size[N], times, vis[N];
LL val[N], c[N];
bool sign[N];

void tarjan(int x){
	dfn[x] = low[x] = ++dfs_clock;
	size[x] = 1;
	for(int i = head[x]; i; i = nxt[i])
		if (!dfn[to[i]]){
			fa[to[i]] = x;
			tarjan(to[i]);
			size[x] += size[to[i]];
			low[x] = min(low[x], low[to[i]]);
			if (low[to[i]] > dfn[x]){// must be " < "
				sign[to[i]] = sign[x] = 1;
				yes[i] = yes[i ^ 1] = 1;
			}
		}else if (to[i] != fa[x]) low[x] = min(low[x], dfn[to[i]]);
}

void addedge(int x, int num){
	vis[x] = times;
	for(int i = head[x]; i; i = nxt[i])
		if (vis[to[i]] != times){
			addedge(to[i], num);
			if (sign[to[i]] && sign[x] && yes[i]){
				val[to[i]] = 1LL * size[to[i]] * (num - size[to[i]]) * l[i];
				ins(x, to[i], val[to[i]]);
			}
		}
}

void init(){
	dfs_clock = 0;
	cnt = cnt2 = 1;
	memset(head, 0, sizeof head);
	memset(hd, 0, sizeof hd);
	memset(yes, 0, sizeof yes);

	memset(dfn, 0, sizeof dfn);
	memset(low, 0, sizeof low);
	memset(fa, 0, sizeof fa);
	memset(val, 0, sizeof val);
	memset(sign, 0, sizeof sign);
	memset(c, 0, sizeof c);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++) scanf("%lld", &c[i]);
	int x, y, z;
	for(int i = 1; i <= m; i ++){
		scanf("%d%d%d", &x, &y, &z);
		add(x, y, z);
	}
}
LL current[N], Lim;
bool treedp(int x){
	vis[x] = times;
	current[x] = c[x];
	for(int i = hd[x]; i; i = nt[i])
		if (vis[t[i]] != times){
			if (!(treedp(t[i]))) return 0;
			if (current[t[i]] + len[i] > Lim) current[x] += len[i];
			if (current[x] > Lim) return 0;
		}
	return 1;
}

bool check(LL x){
	Lim = x;
	times ++;
	for(int i = 1; i <= n; i ++)
		if (vis[i] != times)
			if (!treedp(i)) return 0;
	return 1;
}
void work(){
	for(int i = 1; i <= n; i ++) if (!dfn[i]){
		fa[i] = -1;
		tarjan(i);
	}
	times = 1;
	for(int i = 1; i <= n; i ++)
		if (fa[i] == -1) addedge(i, size[i]);
	LL l = 0, r = 1e18, mid, ans = 0;
	for(int i = 1; i <= n; i ++) l = max(l, c[i]);
	while(l <= r){
		mid = (l + r) >> 1;
		if (check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	printf("%lld\n", ans);
}

int main(){
	int T, cs = 0;
	scanf("%d", &T);
	while(cs < T){
		cs ++;
		printf("Case %d: ", cs);
		init();
		work();
	}
	return 0;
}
