#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 60;
const int dx[] = {1, -1, 0, 0},
	  	  dy[] = {0, 0, 1, -1};

int mp[N][N], n, m, k;
char s[N][N];
typedef pair<int,int> pii;
vector<pii >lake;

int times = 0, vis[N][N];
int find(int x, int y) {
	vis[x][y] = times;
	if (x < 1 || x > n || y < 1 || y > m) return -1;
	int ans = 1;
	for(int i = 0; i < 4; i ++) {
		int tx = x + dx[i], ty = y + dy[i];
		if (mp[tx][ty] || vis[tx][ty]) continue;
		int v = find(tx, ty);
		if (v < 0) ans = -1;
		else ans += v;
	}
	return ans;
}
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; i ++) {
		scanf("%s", s[i] + 1);
		for(int j = 1; j <= m; j ++)
			mp[i][j] = s[i][j] == '*';
	}
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			if (!mp[i][j] && !vis[i][j]) {
				times ++;
				int v = find(i, j);
				if (v > 0) lake.push_back(make_pair(v, times));
			}
	sort(lake.begin(), lake.end());
	int ans = 0;
	for(int i = 0; i < lake.size() - k; i ++) {
		ans += lake[i].first;
		int t = lake[i].second;
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++)
				if (vis[i][j] == t) mp[i][j] = 1;
	}
	printf("%d\n", ans);
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= m; j ++)
			if (mp[i][j]) putchar('*');
			else putchar('.');
		puts("");
	}
	return 0;
}
