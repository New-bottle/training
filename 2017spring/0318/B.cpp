#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 200010;

int n, p[N];
vector<int>a;

bool vis[N];

void dfs(int x)
{
	a[x] = p[x];
}

int ans = 0, route[N][2];
void solve()
{
	memset(vis, 0, sizeof vis);
	for (int i = 1; i <= n; ++i)
		if (p[i] != i) vis[i] = 1;
	for (int i = 1; i <= n; ++i)
		if (p[i] == i) a.push_back(i);
	for (int i = 1; i < (int)a.size(); i += 2) {
		++ans;
		route[ans][0] = a[i - 1];
		route[ans][1] = a[i];
		swap(p[a[i - 1]], p[a[i]]);
	}
	if (a.size() & 1) {
		++ans;
		for (int i = 1; i <= n; ++i)
			if (p[i] != i) {
				route[ans][0] = i;
				route[ans][1] = a[a.size() - 1];
				break;
			}
	}
	printf("%d\n", ans);
	for (int i = 1; i <= ans; ++i)
		printf("%d %d\n", route[i][0], route[i][1]);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &p[i]);
	solve();
	return 0;
}
