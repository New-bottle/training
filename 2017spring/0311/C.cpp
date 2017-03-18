#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100010;
int to[N << 1], nxt[N << 1], head[N], cnt;
void add(int x, int y)
{
	to[++cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
	to[++cnt] = x; nxt[cnt] = head[y]; head[y] = cnt;
}

int n, m, num[N], odd[N], du[N], belong[N], tot;
vector<int>have[N];
bool vis[N];

void dfs(int x)
{
	belong[x] = tot;
	vis[x] = 1;
	for (int i = head[x]; i; i = nxt[i])
		if (!vis[to[i]])
			dfs(to[i]);
}

int ans, route[N << 1];
void getans(int x)
{
	route[++ans] = x;
	vis[x] = 1;
	for (int i = head[x]; i; i = nxt[i])
		if (!vis[to[i]]) {
			getans(to[i]);
			route[++ans] = x;
		}
}
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		static int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);
		++du[x]; ++du[y];
	}

	for (int i = 1; i <= n; ++i) {
		if (!vis[i]) {
			++tot;
			dfs(i);
		}
	}
	for (int i = 1; i <= n; ++i)
		if (du[i] & 1) {
			++odd[belong[i]];
			have[belong[i]].push_back(i);
		}
	for (int i = 1; i <= tot; ++i)
		for (int j = 1; j < (int)have[i].size() - 1; j += 2)
			add(have[i][j - 1], have[i][j]);

	memset(vis, 0, sizeof vis);
	for (int i = 1; i <= n; ++i)
		if (!vis[i] && (du[i] & 1)) getans(i);
	printf("%d\n", ans);
	for (int i = 1; i <= ans; ++i)
		printf("%d%c", route[i], i == ans ? '\n' : ' ' );
	return 0;
}
