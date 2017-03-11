#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100010;
typedef long long LL;
const LL INF = 1e18;

int to[N << 1], nxt[N << 1], head[N], cnt, len[N << 1];
void add (int x, int y, int z)
{
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt; len[cnt] = z;
	to[++ cnt] = x; nxt[cnt] = head[y]; head[y] = cnt; len[cnt] = z;
}

vector<int> c;
bool yes[N], s[N], t[N], inq[N];
int n, m, from[N], x, y;

LL d[N], ans;

queue<int> Q;
void spfa()
{
	for (int i = 1; i <= n; ++i) d[i] = INF;
	for (int i = 0; i < (int)c.size(); ++i) 
		if (s[c[i]]) {
			from[c[i]] = c[i];
			d[c[i]] = 0;
			Q.push(c[i]);
			inq[c[i]] = 1;
		}
	while (!Q.empty()) {
		int x = Q.front(); Q.pop();
		inq[x] = 0;
		for (int i = head[x]; i; i = nxt[i])
			if (d[to[i]] > d[x] + len[i]) {
				d[to[i]] = d[x] + len[i];
				from[to[i]] =from[x];
				if (!inq[to[i]]) {
					Q.push(to[i]);
					inq[to[i]] = 1;
				}
			}
	}
	for (int i = 0; i < (int)c.size(); ++i)
		if (t[c[i]])
			if (ans > d[c[i]]) {
				x = from[c[i]]; y = c[i];
				ans = d[c[i]];
			}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &yes[i]);
		if (yes[i]) c.push_back(i);
	}
	for (int i = 1; i <= m; ++i) {
		static int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		add(x, y, z);
	}
	ans = INF;
	for (int i = 0; i < 18; ++i) {
		memset(s, 0, sizeof s);
		memset(t, 0, sizeof t);
		for (int j = 0; j < (int)c.size(); ++j)
			if (c[j] >> i & 1)
				s[c[j]] = 1;
			else 
				t[c[j]] = 1;
		spfa();
	}
	if (ans == INF) puts("No luck at all");
	else {
		cout << ans << endl;
		cout << x << ' ' << y << endl;
	}
	return 0;
}
