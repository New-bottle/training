#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 200010;
int to[N], nxt[N], head[N], cnt;
int t[N], nt[N], hd[N], cnt2;
void add(int x, int y)
{
	to[++cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
}
void ins(int x, int y)
{
	t[++cnt2] = y;; nt[cnt2] = hd[x]; hd[x] = cnt2;
}

int n, m, d[2][N], dist[N], a, b;
bool vis[N];

void bfs(int S, int d[])
{
	queue<int>Q;
	memset(vis, 0, sizeof vis);
	for (int i = 0; i <= n; ++i) d[i] = -1;
//	memset(d, -1, sizeof d);
	Q.push(S);
	d[S] = 0;
	while(!Q.empty())
	{
		int x = Q.front(); Q.pop();
		for (int i = head[x]; i; i = nxt[i])
			if (d[to[i]] == -1) {
				Q.push(to[i]);
				d[to[i]] = d[x] + 1;
			}
	}
}

int main()
{
	scanf("%d%d%d%d", &n, &m, &a, &b);
	for (int i = 1; i <= m; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		ins(x, y);
		add(y, x);
	}
	bfs(a, d[0]); bfs(b, d[1]);
	queue<int>Q;
	memset(dist, -1, sizeof dist);
	dist[0] = 0;
	Q.push(0);
	while (!Q.empty()) {
		int x = Q.front(); Q.pop();
		for (int i = hd[x]; i; i = nt[i])
			if (dist[t[i]] == -1) {
				Q.push(t[i]);
				dist[t[i]] = dist[x] + 1;
			}
	}
	int ans = 1e9;
	for (int i = 0; i <= n; ++i) {
		if (d[0][i] == -1 || d[1][i] == -1 || dist[i] == -1) continue;
		ans = min(ans, dist[i] + d[0][i] + d[1][i]);
//		printf("i = %d dist = %d\n", i, dist[i] + d[0][i] + d[1][i]);
	}
	printf("%d\n", ans);
	return 0;
}
