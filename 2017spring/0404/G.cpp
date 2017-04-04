#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 10;
const int dx[] = {1, 0, -1, 0},
	      dy[] = {0, 1, 0, -1};

struct graph {
	char a[6][7];
	char* operator [] (int x) {return a[x];}
	const char* operator [] (int x) const {return a[x];}
	void drop() 
	{
		cout << "Dropping" << endl;
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 6; ++j) putchar(a[i][j]); puts("");
		}
		for (int i = 4; i >= 0; --i)
			for (int j = 0; j < 6; ++j)
				if (a[i][j] == 0) {
					for (int k = i; k; --k) swap(a[k][j], a[k - 1][j]);
				}
		cout << "Drop end" << endl;
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 6; ++j) putchar(a[i][j]); puts("");
		}
	}
	void left()
	{
		for (int j = 0; j < 6; ++j)
			while (!a[5][j]) {
				int l = -1;
				for (int k = j + 1; k < 6; ++k) if (a[5][k]) {
					l = k;
					break;
				}
				if (l == -1) return;
				for (int t = 0; t + l < 6; ++t)
					for (int i = 0; i < 5; ++i) {
						swap(a[i][t + j], a[i][t + l]);
//						a[i][t + l] = 0;
					}
			}
	}
	void out()
	{
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 6; ++j) putchar(a[i][j]);
			puts("");
		}
	}
}a, st[20];

bool yes = 0, vis[20][5][6];
int belong[20][5][6], size[20][5][6], tot[20];
int bfs(int dep, int x, int y, bool vis[5][6], const graph& mp, int belong[5][6])
{
	int ans = 1;
	belong[x][y] = tot[dep];
	vis[x][y] = 1;
	for (int k = 0; k < 4; ++k) {
		int tx = x + dx[k], ty = y + dy[k];
		if (tx < 0 || tx > 4 || ty < 0 || ty > 5) continue;
		if (!vis[tx][ty] && mp[tx][ty] == mp[x][y])
			ans += bfs(dep, tx, ty, vis, mp, belong);
	}
	return ans;
}
void dfs (int dep) 
{
	cout << "Dep = " << dep << endl;
	st[dep].out();
	if (yes) return;
	if (st[dep][4][0] == 0) {
		yes = 1;
		return;
	}
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 6; ++j) vis[dep][i][j] = 0;
	tot[dep] = 0;
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 6; ++j)
			if (st[dep][i][j] && !vis[dep][i][j]) {
				++tot[dep];
				size[dep][i][j] = bfs(dep, i, j, vis[dep], st[dep], belong[dep]);
			}
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 6; ++j) if (size[dep][i][j] > 1) {
			int k = belong[dep][i][j];
			st[dep + 1] = st[dep];
			for (int i = 0; i < 5; ++i)
				for (int j = 0; j < 5; ++j)
					if (belong[dep][i][j] == k) st[dep + 1][i][j] = 0;
			st[dep + 1].drop();
			st[dep + 1].left();
			dfs(dep + 1);
		}
}
int main()
{
	int T, cs = 0;
	scanf("%d", &T);
	while (T--) {
		printf("Case %d: ", ++cs);
		for (int i = 0; i < 5; ++i)
			for (int j = 0; j < 6; ++j) cin >> a[i][j];
		yes = 0;
		st[1] = a;
		dfs(1);
		if (yes) puts("Yes");
		else puts("No");
//		for (int i = 0; i < 5; ++i) cout << a[i] << endl;
	}
	return 0;
}
