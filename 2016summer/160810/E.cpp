#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 52;
int n, m;
typedef pair<int,int> pii;
vector<pii > jel[26], hol[26];
char s[N][N];
bool mp[N][N], can[N][N][N][N], yes[N][N][N][N];
int f[N][N][N][N];

void init(){
	for(int i = 0; i < 26; i ++) jel[i].clear(), hol[i].clear();
	for(int i = 1; i <= n; i ++) {
		scanf("%s", s[i] + 1);
		for(int j = 1; j <= m; j ++){
			if (s[i][j] >= 'a' && s[i][j] <= 'z')
				jel[s[i][j] - 'a'].push_back(make_pair(i,j));
			else if (s[i][j] >= 'A' && s[i][j] <= 'Z')
				hol[s[i][j] - 'A'].push_back(make_pair(i,j));
			mp[i][j] = !(s[i][j] == '#');
		}
	}//init
}

int solve(int x1, int y1, int x2, int y2){
	if (f[x1][y1][x2][y2]) return f[x1][y1][x2][y2];
	int x, y, tx, ty;
	for(int i = 0; i < 26; i ++)
		for(int j = 0; j < jel[i].size(); j ++) {
			x = jel[i][j].first; y = jel[i][j].second;
			if (can[x1][y1][x][y]){
				for(int k = 0; k < hol[i].size(); k ++) {
					tx = hol[i][k].first; ty = hol[i][k].second;
					if (can[x][y][tx][ty] && can[tx][ty][x2][y2]) {
						int t1 = 0, t2 = 0;
						if (can[x + 1][y][tx - 1][ty]) t1 = max(t1, solve(x + 1, y, tx - 1, ty));
						if (can[x][y + 1][tx - 1][ty]) t1 = max(t1, solve(x, y + 1, tx - 1, ty));
						if (can[x + 1][y][tx][ty - 1]) t1 = max(t1, solve(x + 1, y, tx, ty - 1));
						if (can[x][y + 1][tx][ty - 1]) t1 = max(t1, solve(x, y + 1, tx, ty - 1));

						if (can[tx + 1][ty][x2][y2]) t2 = max(t2, solve(tx + 1, ty, x2, y2));
						if (can[tx][ty + 1][x2][y2]) t2 = max(t2, solve(tx, ty + 1, x2, y2));
						f[x1][y1][x2][y2] = max(f[x1][y1][x2][y2], t1 + t2 + 1);
					}
				}
			}
		}
	return f[x1][y1][x2][y2]; 
}

void work(){
	memset(can, 0, sizeof can);
	can[n][m][n][m] = 1;
	for(int i = n; i >= 1; i --)
		for(int j = m; j >= 1; j --) if (mp[i][j]){
			can[i][j][i][j] = 1;
			for(int x = i; x <= n; x ++)
				for(int y = j; y <= m; y ++)
					can[i][j][x][y] |= can[i + 1][j][x][y] | can[i][j + 1][x][y];
		}
	if (!can[1][1][n][m]) {
		puts("-1");
		return;
	}
	memset(yes, 0, sizeof yes);
	for(int i = 0; i < 26; i ++)
		for(int j = 0; j < jel[i].size(); j ++)
			for(int k = 0; k < hol[i].size(); k ++)
				yes[jel[i][j].first][jel[i][j].second][hol[i][k].first][hol[i][k].second]
					= can[jel[i][j].first][jel[i][j].second][hol[i][k].first][hol[i][k].second];
	memset(f, 0, sizeof f);
	printf("%d\n", solve(1, 1, n, m));
}

int main(){
	while(scanf("%d%d", &n, &m) == 2 && n && m){
		init();
		work();
	}
	return 0;
}
