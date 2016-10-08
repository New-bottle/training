#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 52;

char s[N][N];
int mp[N][N], n, m, k, now;

char tmp[1010], ans[1010];
bool yes[26], vis[N][N];
void update() {
	Q.push(make_pair(1, 1));
	memset(vis, 0, sizeof vis);
	while(!Q.empty()) {
		int x = Q.front().first, y = Q.front().second; Q.pop();
		for(int i = 0; i < 4; i ++) {
			int tx = x + dx[i], ty = y + dy[i];
			if (tx < 1 || tx > n || ty < 1 || ty > m) continue;
			if (!yes[s[tx][ty] - 'a'] && s[tx][ty] != 'T') continue;
			s
		}
	}
}
void dfs(int x) {
	if (x == 26) update();
	else {
		if (now == k) dfs(x + 1);
		else if (26 - x == k - now) {
			yes[x] = 1;
			now ++;
			dfs(x + 1);
			yes[x] = 0;
			now --;
		} else {
			for(int i = 0; i < 2; i ++) {
				yes[x] = i;
				now += yes[x];
				dfs(x + 1);
				now -= yes[x];
				yes[x] = 0;
			}
		}
	}
}

int main(){
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; i ++)
		scanf("%s", s[i] + 1);
	dfs(0);
	return 0;
}
