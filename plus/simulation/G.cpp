#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef pair<int,int> pii;
const int dx[] = {1, 0, 0, -1},
	  	  dy[] = {0, 1, -1, 0};
const char s[] = {'D', 'R', 'L', 'U'};
int mp[8][8];

inline int id(char ch) {
	if (ch == 'F') return 1;
	if (ch == 'W') return 2;
	if (ch == 'P') return 3;
	if (ch == 'L') return 4;
	if (ch == 'D') return 5;
	if (ch == 'C') return 6;
	return 0;
}

namespace check {
	int a[8][8];
	bool sign[8][8], vis[8][8];
	void flood(int x, int y, int col) {
		vis[x][y] = 1;
		a[x][y] = 0;
		for(int i = 0; i < 4; i ++) {
			int tx = x + dx[i], ty = y + dy[i];
			if (sign[tx][ty] && !vis[tx][ty] && a[tx][ty] == col)
				flood(tx, ty, col);
		}
	}
	void fall(int col) {
		for(int i = 5; i; i --) if (!a[i][col]) {
			int r = 0;
			for(int j = i - 1; j; j --)
				if (a[j][col]) {
					r = j;
					break;
				}
			if (r) a[i][col] = a[r][col], a[r][col] = 0;
			else break;
		}
	}
	void print() {
		for(int i = 1; i <= 5; i ++) {
			for(int j = 1; j <= 6; j ++) printf("%d ", a[i][j]);
			puts("");
		}
		puts("");
	}
	pii check() {
		memcpy(a, mp, sizeof(mp));
		int combo, drop, tc, td;
		combo = drop = 0;
#ifdef debug
		print();
#endif
		do {
			memset(sign, 0, sizeof sign);
			memset(vis, 0, sizeof vis);
			tc = td = 0;
			int len, x, y;
			for(int i = 1; i <= 5; i ++)
				for(int j = 1; j <= 6; j ++) if (a[i][j]) {
					x = i; y = j; len = 1;
					while(a[x + 1][y] == a[i][j]) x++, len++;
					if (len >= 3)
						for(int t = 0; t < len; t ++) sign[i + t][j] = 1;

					x = i; y = j; len = 1;
					while(a[x][y + 1] == a[i][j]) y++, len++;
					if (len >= 3)
						for(int t = 0; t < len; t ++) sign[i][j + t] = 1;
				}
#ifdef debug
			print();
#endif
			for(int i = 1; i <= 5; i ++)
				for(int j = 1; j <= 6; j ++)
					if (sign[i][j]) td ++;
			for(int i = 1; i <= 5; i ++)
				for(int j = 1; j <= 6; j ++) if (!vis[i][j] && sign[i][j]) {
					tc ++;
					flood(i, j, a[i][j]);
				}
			for(int j = 1; j <= 6; j ++) fall(j);
			combo += tc; drop += td;
		} while(tc);
		return make_pair(combo, drop);
	}
}

struct pile {
	int x, y, combo, drop, len;
	char s[12];
	pile() {
		x = y = combo = drop = len = 0;
		memset(s, 0, sizeof s);
	}
	friend bool operator < (const pile &a, const pile &b) {
		if (a.combo != b.combo) return a.combo < b.combo;
		else if (a.drop != b.drop) return a.drop > b.drop;
		else return a.len > b.len;
	}
	void print() {
		printf("Combo:%d Length:%d\n", combo, len);
		printf("%d %d\n", x, y);
		puts(s + 1);
	}
}tmp, ans;

pii t;
int times[8][8], now[13];
void dfs(int x, int y, int lx, int ly) {
	for(int i = 0; i < 4; i ++) {
		int tx = x + dx[i], ty =  y + dy[i];
		if (tx < 1 || tx > 5 || ty < 1 || ty > 6) continue;
		if (tmp.len == 0 && mp[x][y] == mp[tx][ty]) continue;
//		if (times[tx][ty] > 1) continue;
		if (tx == lx && ty == ly) continue;
		tmp.len ++;
		tmp.s[tmp.len] = s[i];
//		now[tmp.len] = mp[tx][ty];
		swap(mp[x][y], mp[tx][ty]);
		if (true || tmp.len > 1 || mp[x][y] != mp[tx][ty]) {
			t = check::check();
			tmp.combo = t.first;
			tmp.drop = t.second;
#ifdef debug
			tmp.print();
#endif
			if (ans < tmp) ans = tmp;
		}
		/*
		if (now[tmp.len] != now[0]) {
			t = check::check();
			tmp.combo = t.first;
			tmp.drop = t.second;
			if (ans < tmp) ans = tmp;
		}
		*/
		if (tmp.len != 9) dfs(tx, ty, x, y);
		tmp.s[tmp.len] = '\0';
		tmp.len --;
		swap(mp[x][y], mp[tx][ty]);
	}
}

int main(){
	int T;
	scanf("%d", &T);
	for(int cs = 1; cs <= T; cs ++) {
		printf("Case #%d:\n", cs);
		for(int i = 1; i <= 5; i ++) {
			char s[10];
			scanf("%s", s + 1);
			for(int j = 1; j <= 6; j ++) mp[i][j] = id(s[j]);
		}
		ans = pile();
		for(int i = 1; i <= 5; i ++)
			for(int j = 1; j <= 6; j ++) {
				tmp = pile();
				tmp.x = i; tmp.y = j;
				now[0] = mp[i][j];
				dfs(i, j, -1, -1);
			}
//		/*
		if (ans.combo == 0) {
			ans.x = ans.y = 1;
			ans.len = 1;
			ans.s[1] = 'D';
		}
//		*/
		ans.print();
	}
	return 0;
}

