#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 310;
const int INF = 1e9 + 7;
struct edge{
	int x, y, v;
	bool operator < (const edge &b) const {
		return v < b.v;
	}
}e[N * N];

int mp[N][N], d[N][N], n, cnt, fa[N];

int getfa(int x) {return fa[x] == x ? x : fa[x] = getfa(fa[x]);}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++) {
			scanf("%d", &mp[i][j]);
			if (i < j) e[++ cnt] = (edge){i, j, mp[i][j]};
		}
	sort(e + 1, e + cnt + 1);
	/*
	for(int i = 1; i <= n; i ++) fa[i] = i;
	int ans = 0;
	for(int i = 1; i <= cnt; i ++) {
		int fx = getfa(e[i].x), fy = getfa(e[i].y);
		if (fx != fy) {
			fa[fx] = fy;
			ans ++;
		}
	}
	*/
	int ans = n * (n - 1) / 2;
	for(int i = 1; i <= n; i ++)
		for(int j = i + 1; j <= n; j ++)
			for(int k = 1; k <= n; k ++)
				if (k != i && k != j && mp[i][j] == mp[i][k] + mp[k][j]) {
					ans --;
					break;
				}
	/*
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++) d[i][j] = (i == j) ? 0 : INF;

	int ans = 0;
	for(int i = 1; i <= cnt; i ++) {
		int x = e[i].x, y = e[i].y, l = e[i].v;
		if (d[x][y] > l) {
			for(int u = 1; u <= n; u ++)
				for(int v = u + 1; v <= n; v ++)
					if (d[u][v] > d[u][x] + l + d[v][y])
						d[u][v] = d[v][u] = d[u][x] + l + d[v][y];
			ans ++;
		}
	}
	*/
	printf("%d\n", ans);
	return 0;
}
