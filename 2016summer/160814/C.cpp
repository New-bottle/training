#include <cstdio>
#include <cstring>
#include <vector>

const int N = 100100;
const int M = 200200;

int nrbegin[N];
int nrto[M];
int nredge[M];
int nrnext[M];
int nrn;

int cost[N];
int value[N];

std::pair<int, int> max2[N][2];

int dp0[N];
int dp1[N];
int dp2[N];
int dp3[N];

int n;

void nradde(int s, int t, int c, int e)
{
	++nrn;
	nrnext[nrn] = nrbegin[s];
	nrto[nrn] = t;
	nredge[nrn] = e;
	nrbegin[s] = nrn;
	cost[e] = c;
}

void readtree()
{
	std::memset(nrbegin, 0, sizeof(nrbegin));
	nrn = 0;

	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", value + i);
	}
	for (int i = 1; i < n; ++i) {
		int s, t, c;
		scanf("%d%d%d", &s, &t, &c);
		nradde(s, t, c, i);
		nradde(t, s, c, i);
	}
}

int dfs0(int node, int pa)
{
	int ans = value[node];
	for (int e = nrbegin[node]; e; e = nrnext[e]) {
		int son = nrto[e];
		if (son == pa)
			continue;
		ans += std::max(0, dfs0(son, node) - 2 * cost[nredge[e]]);
	}
	return dp0[node] = ans;
}

inline void do_dp0()
{
	dfs0(1, 0);
}

void dfs1(int node, int pa)
{
	for (int e = nrbegin[node]; e; e = nrnext[e]) {
		int son = nrto[e];
		if (son == pa)
			continue;
		dp1[son] = std::max(0, dp0[node] + dp1[node] - std::max(0, dp0[son] - 2 * cost[nredge[e]]) - 2 * cost[nredge[e]]);
		dfs1(son, node);
	}
}

inline void do_dp1()
{
	dp1[1] = 0;
	dfs1(1, 0);
}

int dfs2(int node, int pa)
{
	int ans = value[node];
	int m1p = -1, m1v = ans;
	int m2p = -1, m2v = ans;
	int base = dp0[node];
	for (int e = nrbegin[node]; e; e = nrnext[e]) {
		int son = nrto[e];
		if (son == pa)
			continue;
		int chd = dfs2(son, node);
		int m = std::max(0, chd - cost[nredge[e]]) - std::max(0, dp0[son] - 2 * cost[nredge[e]]);
		int bns = m + base;
		if (bns > m1v) {
			m2p = m1p;
			m2v = m1v;
			m1p = son;
			m1v = bns;
		} else if (bns > m2v) {
			m2p = son;
			m2v = bns;
		}
		ans = std::max(ans, bns);
	}
	max2[node][0] = {m1p, m1v};
	max2[node][1] = {m2p, m2v};
	return dp2[node] = ans;
}

inline void do_dp2()
{
	dfs2(1, 0);
}

void dfs3(int node, int pa)
{
	for (int e = nrbegin[node]; e; e = nrnext[e]) {
		int son = nrto[e];
		if (son == pa)
			continue;
		int sans = 0;
		if (max2[node][0].first != son)
			sans = std::max(sans, max2[node][0].second);
		else
			sans = std::max(sans, max2[node][1].second);
		sans += dp1[node] - std::max(0, dp0[son] - 2 * cost[nredge[e]]);

		int sbns = dp3[node] + dp0[node] - std::max(0, dp0[son] - 2 * cost[nredge[e]]);
		dp3[son] = std::max(0, std::max(sans, sbns) - cost[nredge[e]]);
		dfs3(son, node);
	}
}

inline void do_dp3()
{
	dp3[1] = 0;
	dfs3(1, 0);
}

void collect()
{
	for (int i = 1; i <= n; ++i) {
		printf("%d\n", std::max(dp2[i] + dp1[i], dp0[i] + dp3[i]));
	}
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; ++i) {
		printf("Case #%d:\n", i);
		readtree();
		do_dp0();
		do_dp1();
		do_dp2();
		do_dp3();
		collect();
	}
}
