#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 210, M = 130;
const int dx[] = {1, 0, 0, -1},
	  	  dy[] = {0, 1, -1, 0};

int d[N][N][4][M];
int n, m, mp[N][N], stx, sty, edx, edy, num;
char s[N][N];

void bfs() {
	for(int i = 0; i < 4; i ++)
		Q.push((node){stx, sty, i, 0});
}
int main(){
	while(scanf("%d%d", &n, &m) != EOF) {
		num = 0;
		for(int i = 1; i <= n; i ++) {
			scanf("%s", s[i] + 1);
			for(int j = 1; j <= m; j ++) {
				if (s[i][j] == 'S') {
					stx = i; sty = j;
					mp[i][j] = -1;
				}
				if (s[i][j] == 'E') {
					edx = i; edy = j;
					mp[i][j] = -1;
				}
				if (s[i][j] == 'K') mp[i][j] = num++;
				if (s[i][j] == '.') mp[i][j] = -1;
				if (s[i][j] == '#') mp[i][j] = 0;
			}
		}
		bfs();
	}
	return 0;
}
