#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int dx[] = {1, -1, 0, 0},
	  	  dy[] = {0, 0, 1, -1};
int n, num, belong[12][12];
bool vis[12][12];
char s[12][12];
int floodfill(int x, int y){
	belong[x][y] = num;
	int ans = 0;
	for(int i = 0; i < 4; i ++){
		int tx = x + dx[i], ty = y + dy[i];
		if (vis[tx][ty]) continue;
		vis[tx][ty] = 1;
		if (s[tx][ty] == '.') ans ++;
		if (s[tx][ty] == 'o') ans += floodfill(tx, ty);
	}
	return ans;
}

bool check(){
	for(int i = 1; i <= 9; i ++)
		for(int j = 1; j <= 9; j ++)
			if (s[i][j] == 'o' && !belong[i][j]){
				num ++;
				memset(vis, 0, sizeof vis);
				if (floodfill(i, j) == 1) return 1;
			}
	return 0;
}
int main(){
	int T, cs = 0;
	scanf("%d", &T);
	while(cs < T){
		printf("Case #%d: ", ++ cs);
		memset(belong, 0, sizeof belong);
		memset(vis, 0, sizeof vis); num = 0;
		for(int i = 1; i <= 9; i ++)
			scanf("%s", s[i] + 1);
		for(int i = 0; i <= 10; i ++)
			s[0][i] = s[i][0] = s[10][i] = s[i][10] = 'x';
		if (check()) puts("Can kill in one move!!!");
		else puts("Can not kill in one move!!!");
	}
	return 0;
}
