#include<cstdio>
#include<map>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
//#define debug

typedef long long LL;
const int P = 1e9 + 7;
const int N = 400010;
int to[N << 1], nxt[N << 1], head[N], cnt;
void add(int x, int y){
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
	to[++ cnt] = x; nxt[cnt] = head[y]; head[y] = cnt;
}

LL Pow(LL a, int b){
	LL r = 1;
	while(b){
		if (b & 1) r = r * a % P;
		a = a * a % P;
		b >>= 1;
	}
	return r;
}
int dfn[N], low[N], dfs_clock, bcc, belong[N], top, n,m, fa[N];
vector<int>have[N], G[N];
bool iscut[N];
typedef pair<int,int> pii;
pii st[N];

void tarjan(int x){
	dfn[x] = low[x] = ++ dfs_clock;
	int child = 0;
	for(int i = head[x]; i; i = nxt[i])
		if (!dfn[to[i]]){
			fa[to[i]] = x;
			st[++ top] = make_pair(x, to[i]);
			child ++;
			tarjan(to[i]);
			low[x] = min(low[x], low[to[i]]);
			if (low[to[i]] >= dfn[x]) {
				iscut[x] = 1;
				bcc ++; have[bcc].clear();
				for(;;){
					int u = st[top].first, v = st[top].second;
					top --;
					if (belong[u] != bcc){
						have[bcc].push_back(u);
						belong[u] = bcc;
					}
					if (belong[v] != bcc){
						have[bcc].push_back(v);
						belong[v] = bcc;
					}
					if (x == u && to[i] == v) break;
				}
			}
		}else if (dfn[to[i]] < dfn[x] && to[i] != fa[x]){
			st[++ top] = make_pair(x, to[i]);
			low[x] = min(low[x], dfn[to[i]]);
		}
	if (fa[x] < 0 && child == 1) iscut[x] = 0;
}

int sum[N], cheng[N], w[N];
void rebuild(){
	for(int i = 1; i <= bcc; i ++){
		G[n + i].clear();
		w[n + i] = 1;
		if (have[i].size() <= 1) continue;
		for(int j = 0; j < have[i].size(); j ++){
#ifdef debug
			printf("%d <-> %d\n",n + i, have[i][j]);
#endif
			G[n + i].push_back(have[i][j]);
			G[have[i][j]].push_back(n + i);
		}
	}
}

LL ans = 0;
void dfs(int x){
	cheng[x] = w[x];
	sum[x] = 0;
	for(int i = 0; i < G[x].size(); i ++)
		if (G[x][i] != fa[x]){
			fa[G[x][i]] = x;
			dfs(G[x][i]);
			cheng[x] = 1LL * cheng[x] * cheng[G[x][i]] % P;
			sum[x] = (sum[x] + cheng[G[x][i]]) % P;
		}
}
inline int getfa(int x){return fa[x] == x ? x : fa[x] = getfa(fa[x]);}
int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		for(int i = 1; i <= n; i ++) 
			belong[i] = iscut[i] = head[i] = dfn[i] = low[i] = 0;
		cnt = dfs_clock = bcc = top = 0;
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i ++) scanf("%d", &w[i]);
		int x, y;
		for(int i = 1; i <= m; i ++){
			scanf("%d%d", &x, &y);
			add(x, y);
		}
		for(int i = 1; i <= n; i ++)
			if (!dfn[i]){
				fa[i] = -1;
				top = 0;
				tarjan(i);
			}
		for(int i = 1; i <= n; i ++) G[i].clear();
		rebuild();
		for(int i = 0; i <= n + bcc; i ++) sum[i] = 0, fa[i] = i, cheng[i] = 0;
		sum[0] = 0;
		for(int i = 1; i <= n; i ++)
			if (!cheng[i]){
				fa[i] = i;
				dfs(i);
				sum[0] = (sum[0] + cheng[i]) % P;
			}
		int ans = 0;
#ifdef debug
		printf("sum[0] = %d\n",sum[0]);
		for(int i = 1; i <= n; i ++) printf("cheng[%d] = %d sum[%d] = %d\n",i, cheng[i], i, sum[i]);
#endif
		for(int i = 1; i <= n; i ++){
#ifdef debug
			printf("pre = %d\n", ans);
			printf("cheng[getfa(i)] = %d cheng[i] = %d sum[i] = %d\n", cheng[getfa(i)], cheng[i], sum[i]);
#endif
			ans = ((LL)ans + (LL)i * (sum[0] - cheng[getfa(i)] + (LL)cheng[getfa(i)] * Pow(cheng[i], P - 2) % P + sum[i]) % P + P) % P;
			if (fa[i] == i) ans = (ans - i + P) % P;
//			if (w[i] == 1 || G[i].size() == 0) ans = (ans - i + P) % P;
#ifdef debug
			printf("ans = %d\n", ans);
#endif
		}
		for(int i = 0; i <= bcc; i ++) have[i].clear();
		for(int i = 1; i <= n + bcc; i ++) G[i].clear();
		printf("%d\n", ans);
	}
	return 0;
}
