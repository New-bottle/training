#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
//#define debug

const int N = 17;
const int dx[] = {1, 0, 0, -1},
	  	  dy[] = {0, 1, -1, 0};

int mp[N][N];
char s[N];

int id(char ch) {
	if (ch == 'R') return 1;
	if (ch == 'G') return 2;
	if (ch == 'B') return 3;
	return -1;
}
char color(int x) {
	if (x == 1) return 'R';
	if (x == 2) return 'G';
	if (x == 3) return 'B';
	return '.';
}

int vis[N][N];

inline void Remove(int times) {
	for(int i = 1; i <= 10; i ++)
		for(int j = 1; j <= 15; j ++)
			if (vis[i][j] == times) mp[i][j] = 0;
}
inline void fall(int col) {//mp[][col]
	for(int i = 1; i <= 10; i ++) {
		int ti = 0;
		while (!mp[i][col] && ++ti <= 15) {
			for(int j = i; j < 10; j ++)
				mp[j][col] = mp[j + 1][col],
				mp[j + 1][col] = 0;
		}
	}
}
void Shift() {
	for(int j = 1; j <= 15; j ++)
		if (!mp[1][j]) {
			int r = 0;
			for(int t = j + 1; t <= 15; t ++) if (mp[1][t]) {
				r = t; break;
			}
			if (!r) break;
			for(int i = 1; i <= 10; i ++) mp[i][j] = mp[i][r], mp[i][r] = 0;
		}
}
void print() {
	for(int i = 10; i; i --) {
		for(int j = 1; j <= 15; j ++) printf("%c", color(mp[i][j]));
		puts("");
	}
}

int dfs(int x, int y, int col, int time) {
	vis[x][y] = time;
	int ans = 1;
	for(int i = 0; i < 4; i ++) {
		int tx = x + dx[i], ty = y + dy[i];
		if (mp[tx][ty] != col || vis[tx][ty]) continue;
		ans += dfs(tx, ty, col, time);
	}
	return ans;
}

void solve() {
	int score = 0, move = 0, times = 0, ans, px, py, col, num = 0;
	do {
		times = ans = 0;
		memset(vis, 0, sizeof vis);
		move ++;
		for(int j = 1; j <= 15; j ++)
			for(int i = 1; i <= 10; i ++)
				if (vis[i][j] == 0 && mp[i][j]) {
					int tmp = dfs(i, j, mp[i][j], ++ times);
					if (tmp > ans) {
						ans = tmp;
						col = times;
						px = i; py = j;
					}
				}
#ifdef debug
		for(int i = 10; i; i --) {
			for(int j = 1; j <= 15; j ++) printf("%d ", vis[i][j]); puts("");
		}
#endif
		if (ans <= 1) break;
		num += ans;
		score += (ans - 2) * (ans - 2);
		printf("Move %d at (%d,%d): removed %d balls of color %c, got %d points.\n",
				move, px, py, ans, color(mp[px][py]), (ans - 2) * (ans - 2));
		Remove(col);
		for(int i = 1; i <= 15; i ++) fall(i);
		Shift();
#ifdef debug
		print();
#endif
	} while(ans > 1);
	if (num == 150) score += 1000;
	printf("Final score: %d, with %d balls remaining.\n", score, 150 - num);
}

int main(){
	int T;
	scanf("%d", &T);
	for(int cs = 1; cs <= T; cs ++) {
		printf("Game %d:\n\n", cs);
		for(int i = 10; i; i --) {
			scanf("%s", s + 1);
			for(int j = 1; j <= 15; j ++) mp[i][j] = id(s[j]);
		}
		solve();
		puts("");
	}
	return 0;
}
