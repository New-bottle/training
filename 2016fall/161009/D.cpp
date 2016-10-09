#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;

const int N = 200010;
typedef long long LL;
int n, m;
int dfn[N], low[N], _index, size[N], Bcnt, belong[N];
int s[N], top;
bool instack[N];
vector<int> edge[N];
void tarjan(int u){
	dfn[u] = low[u] = ++_index;
	int sz = edge[u].size();
	s[++ top] = u;
	instack[u] = 1;
	for(int i = 0; i < sz; i ++){
		int v = edge[u][i];
		if(!dfn[v]){
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if(instack[v]){
			low[u] = min(low[u], dfn[v]);
		}
	}
	if(dfn[u] == low[u]){
		int v;
		Bcnt ++;
		do{
			v = s[top --];
			belong[v] = Bcnt;
			size[Bcnt] ++;
			instack[v] = 0;
		}while(u != v);
	}
}

bool out[N], in[N];
void rebuild(){
	for(int u = 1; u <= n; u ++){
		int sz = edge[u].size();
		for(int i = 0; i < sz; i ++){
			int v = edge[u][i];
			if(belong[u] != belong[v]) {
				out[belong[u]] = 1;
				in[belong[v]] = 1;
			}
		}
	}
}

void solve(){
	for(int i = 1; i <= n; i ++){
		if(!dfn[i]) tarjan(i);
	}
	rebuild();
	if (Bcnt == 1) {
		puts("-1");
		return;
	}
	LL ans = 0;
	for(int i = 1; i <= Bcnt; i ++) {
		if (!out[i]) {
			LL total = (LL) n * (n - 1) - (LL)size[i] * (n - size[i]);
			ans = max(ans, total - m);
		}
		if (!in[i]) {
			LL total = (LL) n * (n - 1) - (LL)size[i] * (n - size[i]);
			ans = max(ans, total - m);
		}
	}
	cout << ans << endl;
}

void init(){
	for(int i = 1; i <= n; i ++){
		low[i] = dfn[i] = 0;
		belong[i] = 0;
		edge[i].clear();
		instack[i] = 0;
	}
	for(int i = 1; i <= Bcnt; i ++){
		in[i] = out[i] = size[i] = 0;
	}
	top = 0;
	_index = 0;
	Bcnt = 0;
}
int main(){
	int T;
	scanf("%d", &T);
	for(int cs = 1; cs <= T; cs ++) {
		printf("Case %d: ", cs);
		init();
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= m; i ++) {
			int x, y;
			scanf("%d%d", &x, &y);
			edge[x].push_back(y);
		}
		solve();
	}
	return 0;
}
