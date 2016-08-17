#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int INF = 300010;
const int N = 6010;
vector<int>G[N], f[N], g[N];
vector<int>pre[N], suc[N];

int n, m, v[N], a[N], num, ans, lf[N], lg[N];
 
void dfs(int x, int fa){
	lf[x] = lg[x] = 1;
	if (G[x].size() == 1 && G[x][0] == fa) {
		f[x].resize(2); g[x].resize(2);
		f[x][0] = 0; f[x][1] = a[x];
		g[x][0] = INF; g[x][1] = a[x];
		return;
	}
	for(int i = 0; i < (int)G[x].size(); i ++) {
		int y = G[x][i];
		if (y == fa) continue;
		dfs(y, x);
		if (f[y][lf[y]] < a[x]) lf[x] = max(lf[x], lf[y] + 1);
		else lf[x] = max(lf[x], lf[y]);
		if (g[y][lg[y]] > a[x]) lg[x] = max(lg[x], lg[y] + 1);
		else lg[x] = max(lg[x], lg[y]);
	}
	f[x].resize(lf[x] + 1, INF);
	f[x][0] = 0;
	g[x].resize(lg[x] + 1, 0);
	g[x][0] = INF;
	for(int i = 0; i < (int)G[x].size(); i ++) {
		int y = G[x][i];
		if (y == fa) continue;
		for(int j = 0; j < f[y].size(); j ++) f[x][j] = min(f[x][j], f[y][j]);
		int l = 0, r = lf[y], mid, ans = 0;
		while(l <= r) {
			mid = (l + r) >> 1;
			if (a[x] > f[y][mid]) ans = mid, l = mid + 1;
			else r = mid - 1;
		}
		f[x][ans + 1] = min(f[x][ans + 1], a[x]);

		for(int j = 0; j < g[y].size(); j ++) g[x][j] = max(g[x][j], g[y][j]);
		l = 0; r = lg[y]; ans = 0;
		while(l <= r) {
			mid = (l + r) >> 1;
			if (a[x] < g[y][mid]) ans = mid, l = mid + 1;
			else r = mid - 1;
		}
		g[x][ans + 1] = max(g[x][ans + 1], a[x]);
	}
	//update f[x], g[x] end
	for(int i = 0; i < (int)G[x].size(); i ++) {
		int y = G[x][i];
		if (pre[i].size() < f[x].size()) pre[i].resize(f[x].size(), INF);
		if (y == fa) {
			for(int j = 0; j <= lf[x]; j ++)
				pre[i][j] = i ? pre[i - 1][j] : INF;
			continue;
		}
		for(int j = 0; j < f[y].size(); j ++)
			pre[i][j] = min(i ? pre[i - 1][j] : INF, f[y][j]);
	}
	if (suc[G[x].size()].size() < f[x].size()) suc[G[x].size()].resize(f[x].size(), INF);
	for(int i = G[x].size() - 1; i >= 0; i --) {
		int y = G[x][i];
		if (suc[i].size() < f[x].size()) suc[i].resize(f[x].size(), INF);
		if (y == fa) {
			for(int j = 0; j <= lf[x]; j ++)
				suc[i][j] = i ? suc[i + 1][j] : INF;
			continue;
		}
		for(int j = 0; j < f[y].size(); j ++)
			suc[i][j] = min(i ? suc[i + 1][j] : INF, f[y][j]);
	}
	for(int i = 0; i < (int)G[x].size(); i ++) {
		int y = G[x][i];
		if (y == fa) continue;
		for(int j = 0; j < g[y].size(); j ++) {
			if (i > 0) {
				int l = 0, r = lf[x], mid, p = 0;
				while(l <= r) {
					mid = (l + r) >> 1;
					if (pre[i - 1][mid] < g[y][j]) p = mid, l = mid + 1;
					else r = mid - 1;
				}
				ans = max(ans, j + p);
				if (g[y][j] > a[x]) {
					l = 0, r = lf[x]; p = 0;
					while(l <= r) {
						mid = (l + r) >> 1;
						if (pre[i - 1][mid] < a[x]) p = mid, l = mid + 1;
						else r = mid - 1;
					}
					ans = max(ans, j + p + 1);
				}
			}
			if (i < G[x].size() - 1) {
				int l = 0, r = lf[x], mid, p = 0;
				while(l <= r) {
					mid = (l + r) >> 1;
					if (suc[i + 1][mid] < g[y][j]) p = mid, l = mid + 1;
					else r = mid - 1;
				}
				ans = max(ans, j + p);
				if (g[y][j] > a[x]) {
					l = 0, r = lf[x]; p = 0;
					while(l <= r) {
						mid = (l + r) >> 1;
						if (suc[i + 1][mid] < a[x]) p = mid, l = mid + 1;
						else r = mid - 1;
					}
					ans = max(ans, j + p + 1);
				}
			}
		}
	}
	ans = max(ans, lf[x]);
	ans = max(ans, lg[x]);
	printf("dfs %d %d ans = %d\n", x, fa, ans);
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) {
		scanf("%d", &a[i]);
		v[i] = a[i];
	}
	sort(v + 1, v + n + 1);
	num = unique(v + 1, v + n + 1) - v - 1;
	for(int i = 1; i <= n; i ++)
		a[i] = lower_bound(v + 1, v + num + 1, a[i]) - v;
	for(int i = 1; i < n; i ++) {
		int x, y;
		scanf("%d%d", &x, &y);
		G[x].push_back(y);
		G[y].push_back(x);
//		add(x, y);
	}
	dfs(1, -1);
	/*
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= n; j ++)
			printf("%d ", f[i][j]);
		puts("");
	}
	puts("");
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= n; j ++)
			printf("%d ", g[i][j]);
		puts("");
	}
	*/
	printf("%d\n", ans);
	return 0;
}
