#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int P = 1e9 + 7;
const int N = 200010;
int to[N << 1], nxt[N << 1], head[N], cnt;
void add(int x, int y){
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
	to[++ cnt] = x; nxt[cnt] = head[y]; head[y] = cnt;
}

int w[N], n, m, poi;
bool vis[N];

int dfs(int x){
	vis[x] = 1;
	int ans = w[x];
	for(int i = head[x]; i; i = nxt[i])
		if (!vis[to[i]] && to[i] != poi)
			ans = (LL)ans * dfs(to[i]) % P;
	return ans;
}
int calc(int i){
	int ans = 0;
	poi = i;
	memset(vis, 0, sizeof vis);
	for(int j = 1; j <= n; j ++)
		if (!vis[j] && j != i) ans += dfs(j);
	return ans;
}

int main(){
	freopen("F.in","r",stdin);
	int T;
	scanf("%d", &T);
	int x, y;
	while(T--){
		memset(head, 0, sizeof head);
		cnt = 0;
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i ++)
			scanf("%d", &w[i]);
		for(int i = 1; i <= m; i ++){
			scanf("%d%d", &x, &y);
			add(x, y);
		}
		int ans = 0;
		for(int i = 1; i <= n; i ++){
			ans = (ans + 1LL * calc(i) * i % P) % P;
		}
		printf("%d\n", ans);
	}
	return 0;
}
