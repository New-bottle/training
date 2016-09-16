#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 11;

int a[N][N], belong[N][N];
bool sqr[N][N];
bool used[N][N];
bool found = 0, vis[10];

bool jud(int x, int y) {
	for(int i = 1; i <= 9; i ++)
		for(int j = 1; j <= 9; j ++)
			if (i == x || j == y || belong[i][j] == belong[x][y])
				if (a[x][y] == a[i][j] && (i != x || j != y)) return 0;
	return 1;
}

void dfs(int x, int y) {
	if (found) return;
	if (x == 9 && y == 9) {
		found = 1;
		for(int i = 1; i <= 9; i ++) {
			for(int j = 1; j <= 9; j ++) printf("%d", a[i][j]);
			puts("");
		}
		return;
	}
	if (a[x][y]) {
		if (y == 9) dfs(x + 1, 1);
		else dfs(x, y + 1);
		return ;
	}
	if (a[x + 1][y] == 0 && x < 9) {
		for(int i = 1; i <= 9; i ++)
			for(int j = 1; j <= 9; j ++)
				if (i != j && !used[i][j]) {
					a[x][y] = i;
					a[x + 1][y] = j;
					if (jud(x, y) && jud(x + 1, y)) {
						used[i][j] = used[j][i] = 1;
						if (y == 9) dfs(x + 1, 1);
						else dfs(x, y + 1);
						used[i][j] = used[j][i] = 0;
					}
					a[x][y] = a[x + 1][y] = 0;
				}
	}
	if (a[x][y + 1] == 0 && y < 9) {
		for(int i = 1; i <= 9; i ++)
			for(int j = 1; j <= 9; j ++)
				if (i != j && !used[i][j]) {
					a[x][y] = i;
					a[x][y + 1] = j;
					if (jud(x, y) && jud(x, y + 1)) {
						used[i][j] = used[j][i] = 1;
						if (y == 9) dfs(x + 1, 1);
						else dfs(x, y + 1);
						used[i][j] = used[j][i] = 0;
					}
					a[x][y] = a[x][y + 1] = 0;
				}
	}
}
int main(){
	int cs = 0, n;
	for(int i = 1; i <= 9; i ++)
		for(int j = 1; j <= 9; j ++)
			belong[i][j] = (i - 1) / 3 * 3 + (j - 1) / 3 + 1;
	char p[4];
	while(scanf("%d", &n) != EOF && n) {
		printf("Puzzle %d\n", ++ cs);
		memset(a, 0, sizeof a);
		memset(used, 0, sizeof used);
		int u, v;
		for(int i = 1; i <= n; i ++) {
			scanf("%d", &u);
			scanf("%s", p);
			int x = p[0] - 'A' + 1, y = p[1] - '0';
			a[x][y] = u;
			
			scanf("%d", &v);
			scanf("%s", p);
			x = p[0] - 'A' + 1, y = p[1] - '0';
			a[x][y] = v;
			used[u][v] = used[v][u] = 1;
		}

		for(int i = 1; i <= 9; i ++) {
			int x, y;
			scanf("%s", p);
			x = p[0] - 'A' + 1, y = p[1] - '0';
			a[x][y] = i;
		}
		dfs(1, 1);
		found = 0;
	}
	return 0;
}
