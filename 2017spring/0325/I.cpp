#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 200010;
int to[N << 1], nxt[N << 1], head[N], cnt;
void add (int x, int y)
{
	to[++cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
	to[++cnt] = x; nxt[cnt] = head[y]; head[y] = cnt;
}

int mn[N], du[N], ans[N], n, m;
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);
		++du[x];
		++du[y];
	}
	du[0] = 1e9;
	int who = 0;
	for (int i = 1; i <= n; ++i)
		if (du[i] < du[who]) who = i;
	for (int i = 1; i <= n; ++i) ans[i] = 1;
	for (int i = head[who]; i; i = nxt[i])
		ans[to[i]] = 0;
	ans[who] = 0;
	for (int i = 1; i <= n; ++i) printf("%d%c", ans[i], i == n ? '\n' : ' ');
	return 0;
}
