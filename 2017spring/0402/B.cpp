#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 500010;
int to[N << 1], nxt[N << 1], head[N], cnt;
void add (int x, int y)
{
	to[++cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
	to[++cnt] = x; nxt[cnt] = head[y]; head[y] = cnt;
}
int n, m, belong[N], sum[N], size[N], tot, du[N];

void dfs (int x)
{
	++size[tot];
	belong[x] = tot;
	for (int i = head[x]; i; i = nxt[i])
		if (!belong[to[i]]) dfs(to[i]);
}
int gcd(int a, int b) {return b ? gcd(b, a % b) : a;}
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);
		++du[x]; ++du[y];
	}
	for (int i = 1; i <= n; ++i)
		if (!belong[i]) {
			++tot;
			dfs(i);
		}
	for (int i = 1; i <= n; ++i) sum[belong[i]] += du[i];
	for (int i = 1; i <= n; ++i) {
		int d = gcd(sum[belong[i]] + size[belong[i]], du[i] + 1);
		printf("%d %d\n", (sum[belong[i]] + size[belong[i]]) / d, (du[i] + 1) / d);
	}
	return 0;
}
