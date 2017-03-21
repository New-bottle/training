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
int tot, belong[N][N], num[N][N], cnt;

bool inmap(int x, int y)
{
	return (mp[x][y] == '.' || mp[x][y] == '?') && x >= 1 && x <= n && y >= 1 && y <= m;
}


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
		for (int j = 1; j <= m; ++j) if (belong[i][j] == 0) mp[i][j] = '#';
	if (tot == 1) {
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				if (mp[i][j] == '?') {
					tot = 0;
					mp[i][j] = '#';
					memset(vis, 0, sizeof vis);
					for (int x = 1; x <= n; ++x)
						for (int y = 1; y <= m; ++y)
							if (mp[x][y] == '.' && !vis[x][y]) {
								++tot;
								flood(x, y);
							}
					if (tot == 1) {
						puts("Ambiguous");
						return 0;
					}
					mp[i][j] = '?';
				}
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				if (mp[i][j] == '?') mp[i][j] = '.';
		for (int i = 1; i <= n; ++i) puts(mp[i] + 1);
	} else {
		puts("Impossible");
	}
	return 0;
}
