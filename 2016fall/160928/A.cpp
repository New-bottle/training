#include<cstdio>
#include<queue>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int N = 100010;

vector<int>G[N];
int fa[N][19], n, m, a[N], dep[N];

void dfs(int x) {
	for(int i = 1; (1 << i) <= dep[x]; i ++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for(int i = 0; i < G[x].size(); i ++) {
		dep[G[x][i]] = dep[x] + 1;
		dfs(G[x][i]);
	}
}
int LCA(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	int t = dep[x] - dep[y];
	for(int i = 0; i < 19; i ++)
		if (t >> i & 1) x = fa[x][i];
	for(int i = 18; i >= 0; i --)
		if (fa[x][i] != fa[y][i])
			x = fa[x][i],
			y = fa[y][i];
	if (x == y) return x;
	return fa[x][0];
}

queue<int>Q;
int main(){
	scanf("%d", &n);
	for(int i = 2; i <= n; i ++) {
		scanf("%d", &fa[i][0]);
		G[fa[i][0]].push_back(i);
	}
	for(int i = 1; i <= n; i ++) sort(G[i].begin(), G[i].end());
	dfs(1);
	Q.push(1);
	int t = 0;
	while(!Q.empty()) {
		int x = Q.front(); Q.pop();
		a[++ t] = x;
		for(int i = 0; i < G[x].size(); i ++)
			Q.push(G[x][i]);
	}
	LL ans = 0;
	for(int i = 2; i <= n; i ++) {
		int x = a[i - 1], y = a[i], f = LCA(x, y);
		ans += dep[x] + dep[y] - dep[f] * 2;
	}
	cout << ans << endl;
	return 0;
}
