#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 20;

char mp[N][N], opt[100];

int x, y;
bool yes[N][N];

bool work(char &a, char &b, char &c) {
	if (b == '#') return 0;
	else if (b == 'b') {
		if (c == '.') swap(b, c);
		else return 0;
	}
	swap(a, b);
	return 1;
}
void Up() {
	if (work(mp[x][y], mp[x - 1][y], mp[x - 2][y])) x --;
}
void Down() {
	if (work(mp[x][y], mp[x + 1][y], mp[x + 2][y])) x ++;
}
void Left() {
	if (work(mp[x][y], mp[x][y - 1], mp[x][y - 2])) y --;
}
void Right() {
	if (work(mp[x][y], mp[x][y + 1], mp[x][y + 2])) y ++;
}

void print(int n, int m) {
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= m; j ++) {
			if (yes[i][j]) {
				if (mp[i][j] == 'b') printf("B");
				if (mp[i][j] == 'w') printf("W");
				if (mp[i][j] == '.') printf("+");
			} else {
				printf("%c", mp[i][j]);
			}
		}
		puts("");
	}
}

bool jud(int n, int m) {
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			if (yes[i][j] && mp[i][j] != 'b') return 0;
	return 1;
}

int main(){
	int n, m, cs = 0;
	for(int i = 0; i <= 17; i ++)
		for(int j = 0; j <= 17; j ++)
			mp[i][j] = '#';
	while(scanf("%d%d", &n, &m) != EOF && n && m) {
		printf("Game %d: ", ++ cs);
		for(int i = 1; i <= n; i ++) {
			scanf("%s", mp[i] + 1);
			for(int j = 1; j <= m; j ++) {
				if (mp[i][j] == 'B' || mp[i][j] == 'W' || mp[i][j] == '+')
					yes[i][j] = 1;
				else yes[i][j] = 0;
				if (mp[i][j] == 'w' || mp[i][j] == 'W') x = i, y = j;
				if (mp[i][j] == 'B') mp[i][j] = 'b';
				if (mp[i][j] == 'W') mp[i][j] = 'w';
				if (mp[i][j] == '+') mp[i][j] = '.';
			}
		}
		scanf("%s", opt);
		int l = strlen(opt);
		for(int i = 0; i < l; i ++) {
			if (opt[i] == 'U') Up();
			if (opt[i] == 'D') Down();
			if (opt[i] == 'L') Left();
			if (opt[i] == 'R') Right();
			if (jud(n, m)) break;
//			print(n, m);
//			puts("");
		}
		if (jud(n, m)) puts("complete");
		else puts("incomplete");
		print(n, m);
	}
	return 0;
}
