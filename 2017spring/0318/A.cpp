#include <cstdio>
#include <map>
#include <set>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 60;
const int dx[] = {1, 0, -1, 0},
	      dy[] = {0, 1, 0, -1};

char mp[N][N];
bool vis[N][N];
int n, m;

bool inmap(int x, int y)
{
	return mp[x][y] == '.' && x >= 1 && x <= n && y >= 1 && y <= m;
}

int tot, belong[N][N], num[N][N], cnt;

void flood(int x, int y)
{
	belong[x][y] = tot;
	vis[x][y] = 1;
	for (int i = 0; i < 4; ++i) {
		int tx = x + dx[i], ty = y + dy[i];
		if (inmap(tx, ty) && !vis[tx][ty])
			flood(tx, ty);
	}
}

map<int, int> du[2500];
bool ambi = 0, can = 0, go[2500];

void dfs(int x)
{
	go[x] = 1;
	for (int i = 1; i <= tot; ++i)
		if (du[x][i] && !go[i]) dfs(i);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%s", mp[i] + 1);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if (!vis[i][j] && mp[i][j] == '.') {
				++tot;
				flood(i, j);
			} else if (mp[i][j] == '?') num[i][j] = ++cnt;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if (num[i][j]) {
				set<int>s;
				for (int k = 0; k < 4; ++k) {
					int x = i + dx[k], y = j + dy[k];
					if (mp[x][y] != '.') continue;
					s.insert(belong[x][y]);
				}
				if (s.size() == 0) mp[i][j] = '#';
				if (s.size() == 1) ambi = 1;
				for (set<int>::iterator it = s.begin(), jt; it != s.end(); ++it)
					for (jt = it, ++jt; jt != s.end(); ++jt) {
						++du[*it][*jt];
						++du[*jt][*it];
						if (du[*it][*jt] > 1) ambi = 1;
					}
			}
	dfs(1);
	can = 1;
	for (int i = 1; i <= tot; ++i) if (!go[i]) {
		can = 0;
		break;
	}
	if (can && !ambi) {
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j) if (mp[i][j] == '?') mp[i][j] = '.';
		for (int i = 1; i <= n; ++i) puts(mp[i] + 1);
	} else if (can) {
		puts("Ambiguous");
	} else puts("Impossible");
	return 0;
}
