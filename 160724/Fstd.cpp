#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>
#include <algorithm>

#include <vector>

#define pb push_back
using namespace std;
const int mod = 1e9 + 7;

int tot = 1;

const int maxm = 400005;
const int maxn = 200005;
int e[maxm], nxt[maxm], g[maxn];
int belong[maxn];
bool v[maxn];
int stack[maxn], low[maxn], dfn[maxn], f[maxn];
int c[maxn], w[maxn], prod[maxn], h[maxn], p[maxn];
int q[maxn];
vector<int> E[maxn], ne[maxn];
int n, m, now_sum = 1, D;

bool iscut[maxn];
int dfs_clock = 0, top = 0, sum = 0, res = 0, cntt = 0;
void add(int u, int v)
{
	e[tot] = v; nxt[tot] = g[u]; g[u] = tot ++;
	e[tot] = u; nxt[tot] = g[v]; g[v] = tot ++;
}

int ksm(int x, int y)
{
	int s = 1;
	for (; y; y >>= 1)
	{
		if (y & 1) s = 1LL * s * x % mod;
		x = 1LL * x * x % mod;
	}
	return s;
}

void dfs(int x, int num)
{
	int child = 0;
	belong[x] = res;
	now_sum = 1LL * now_sum * w[x] % mod;
	cntt ++;
	v[x] = 1; dfn[x] = ++ dfs_clock;
	low[x] = dfn[x]; stack[++ top] = x;
	for (int i = g[x]; i; i = nxt[i])
		if (!v[e[i]])
		{
			++ child;
			dfs(e[i], i);
			low[x] = min(low[x], low[e[i]]);
			if (low[e[i]] >= dfn[x])
			{
				int tmp = 0;
				iscut[x] = true; ++ sum;
				E[x].pb(sum);
				do {
					tmp = stack[top --];
					E[tmp].pb(sum);
				}while (tmp != e[i]);
			}
		}
		else if (((i - 1) ^ (num - 1)) != 1) low[x] = min(low[x], dfn[e[i]]);
	if (x == D && child == 1) iscut[x] = false;
}

void dfs2(int x)
{
	v[x] = true;
	prod[x] = x <= n ? w[x] : c[x - n];
	h[x] = 0;
	for (int i = 0; i < (int )ne[x].size(); i ++)
	{
		int to = ne[x][i];
		if (v[to] == true) continue;
		f[to] = x;
		dfs2(to);
	
		prod[x] = 1LL * prod[x] * prod[to] % mod;
		h[x] += prod[to];
		if (h[x] >= mod) h[x] -= mod;
	}
}

int main( )
{
	freopen("F.in","r",stdin);
	int T, x, y;
	scanf("%d", &T);
	while (T --)
	{
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i ++)
			scanf("%d", &w[i]);
		for (int i = 1; i <= m; i ++)
		{
			scanf("%d %d", &x, &y);
			add(x, y);
		}
		int ans = 0;
		for (int i = 1; i <= n; i ++)
			if (!v[i])
			{
				++ res;
				D = i;
				now_sum = 1; cntt = 0;
				dfs(i, 0);
				ans += now_sum;
				p[res] = now_sum;
				q[res] = cntt;
				if (ans >= mod) ans -= mod;
			}
		printf("bcc = %d\n", sum);
		for (int i = 1; i <= n; i ++)
			if (iscut[i])
				for (int j = 0; j < (int )E[i].size(); j ++)
				{
					ne[i].pb(E[i][j] + n);
					ne[E[i][j] + n].pb(i);
				}
		for (int i = 1; i <= sum; i ++) c[i] = 1;
		for (int i = 1; i <= n; i ++)
		{
			if (iscut[i]) continue;
			for (int j = 0; j < (int )E[i].size(); j ++)
				c[E[i][j]] = 1LL * c[E[i][j]] * w[i] % mod;
		}
		int N = n + sum;
		for (int i = 1; i <= N; i ++) v[i] = false;
		for (int i = 1; i <= N; i ++)
			if (!v[i])
				dfs2(i);


		int Ans = 0;
		for (int i = 1; i <= n; i ++)
		{
			if (iscut[i] == false)
			{
				int cur = belong[i];
				int tmp = (ans - p[cur] + mod) % mod;
				if (q[cur] > 1)
				{
					tmp += 1LL * p[cur] * ksm(w[i], mod - 2) % mod;
					tmp %= mod;
				}
				Ans += 1LL * i * tmp % mod;
			}
			else
			{
				int cur = belong[i];
				int tmp = (ans - p[cur] + mod) % mod;
				if (f[i])
				{
					tmp += 1LL * p[cur] * ksm(prod[i], mod - 2) % mod;
					tmp %= mod;
				}
				tmp += h[i];
				tmp %= mod;
				Ans += 1LL * i * tmp % mod;
			}
			Ans %= mod;
		}
		printf("%d\n", Ans);
		for (int i = 1; i <= N; i ++) E[i].clear(), ne[i].clear();
		dfs_clock = 0; sum = 0; res = 0;
		for (int i = 1; i <= N; i ++) v[i] = false, iscut[i] = false;
		for (int i = 1; i <= N; i ++) g[i] = 0, f[i] = 0;
		tot = 1; top = 0;
		sum = 0, res = 0;
	}
	return 0;
}
