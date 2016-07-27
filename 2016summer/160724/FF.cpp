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
const int N = 200010;
const int M = 300010;
int to[M << 1], nxt[M << 1], head[N], cnt;
void add(int x, int y){
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
	to[++ cnt] = x; nxt[cnt] = head[y]; head[y] = cnt;
}
int t[M << 1], nt[M << 1], hd[N], cnt2;
void ins(int x, int y){
	t[++ cnt2] = y; nt[cnt2] = hd[x]; hd[x] = cnt2;
	t[++ cnt2] = x; nt[cnt2] = hd[y]; hd[y] = cnt2;
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
int dfn[N], low[N], dfs_clock, bcc, belong[N], top, n,m, w[N], fa[N];
vector<int>have[N];
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

int mul[N], sum[N], cheng[N];
map<int,int>mp[N];
void rebuild(){
	for(int i = 1; i <= n; i ++) if (iscut[i] || head[i] == 0){
		iscut[i] = 1;
		belong[i] = ++ bcc;
		have[bcc].clear();
		have[bcc].push_back(i);
	}
	int u, v;
	for(int x = 1; x <= n; x ++)
		for(int i = head[x]; i; i = nxt[i]){
			u = belong[x]; v = belong[to[i]];
			if (u == v) continue;
			if (mp[u][v]) continue;
			if (iscut[x] && iscut[to[i]]) continue;
			mp[u][v] = 1;
			mp[v][u] = 1;
			ins(u, v);
		}
	for(int i = 1; i <= bcc; i ++){
		mul[i] = 1;
		for(int j = 0; j < have[i].size(); j ++)
			if (!iscut[have[i][j]] || have[i].size() == 1) mul[i] = mul[i] * w[have[i][j]] % P;
	}
}

LL ans = 0;
void dfs(int x){
	cheng[x] = mul[x];
	sum[x] = 0;
	for(int i = hd[x]; i; i = nt[i])
		if (t[i] != fa[x]){
			fa[t[i]] = x;
			dfs(t[i]);
			cheng[x] = 1LL * cheng[x] * cheng[t[i]] % P;
			sum[x] = (sum[x] + cheng[t[i]]) % P;
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
				tarjan(i);
			}
		rebuild();
		for(int i = 0; i <= bcc; i ++) sum[i] = 0, fa[i] = i, cheng[i] = 0;
		sum[0] = 0;
		for(int i = 1; i <= bcc; i ++)
			if (!cheng[i]){
				dfs(i);
				sum[0] = (sum[0] + cheng[i]) % P;
			}
		ans = 0;
		for(int i = 1; i <= n; i ++){
			x = belong[i];
			if (iscut[i]){
				ans = ((LL)ans + 1LL * i * (sum[0] - cheng[getfa(x)] + ((LL)cheng[getfa(x)] * Pow(cheng[x], P - 2) % P + sum[x]) % P + P) % P) % P;
				if (hd[x] == 0) ans = (ans - i + P) % P;
			}else{
				ans = ((LL)ans + 1LL * i * (sum[0] - cheng[getfa(x)] + (LL)cheng[getfa(x)] * Pow(w[i], P - 2) % P + P) % P) % P;
			}
		}
		for(int i = 1; i <= bcc; i ++) hd[i] = 0, have[i].clear(), mp[i].clear();
		cnt2 = 0;
		cout << ans << endl;
	}
	return 0;
}
