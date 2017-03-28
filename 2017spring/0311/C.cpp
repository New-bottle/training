#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 200010;
int to[N << 2], nxt[N << 2], head[N], cur[N], cnt = 1;
bool del[N << 2];
void add(int x, int y)
{
	to[++cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
	to[++cnt] = x; nxt[cnt] = head[y]; head[y] = cnt;
}

int n, m, num[N], odd[N], du[N], belong[N], tot;
int st[N], top, ans, route[N << 2];
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

void getans(int x)
{
//	printf("getans %d\n", x);
	vis[x] = 1;
	st[++top] = x;
	for (int &i = cur[x]; i; i = nxt[i])
		if (!del[i]) {
			del[i] = del[i ^ 1] = 1;
			getans(to[i]);
			break;
		}
}

void fleury(int x)
{
//	printf("fluery %d\n", x);
	vis[x] = 1;
//	top = 1;
	st[++top] = x;
	while (top)
	{
		int k = 0;
		for (int i = cur[st[top]]; i; i = nxt[i])
			if (!del[i]) {
				k = 1; break;
			}
		if (!k) {
			route[++ans] = st[top--];
//			printf("%d ", st[top]); --top;
		} else {
			--top;
			getans(st[top + 1]);
		}
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
		for (int j = 1; j < (int)have[i].size() - 1; j += 2) {
			add(have[i][j - 1], have[i][j]);
			++du[have[i][j - 1]]; ++du[have[i][j]];
		}

	for (int i = 1; i <= n; ++i) cur[i] = head[i];
	memset(vis, 0, sizeof vis);
	for (int i = 1; i <= n; ++i)
		if ((du[i] & 1) && !vis[i]) fleury(i);
	for (int i = 1; i <= n; ++i)
		if (!vis[i] && du[i]) fleury(i);
	printf("%d\n", ans);
	for (int i = 1; i <= ans; ++i) printf("%d%c", route[i], i == ans ? '\n' : ' ');
	return 0;
}
