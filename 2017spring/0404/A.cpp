#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 110;

char s[10010];
int a[2][N][2], n[2];
bool used[2][N];
char ans[27][1 << 10][1 << 10];
int dfs (int who, int x, int w1, int w2)
{
	if (ans[x][w1][w2] != -1) return ans[x][w1][w2];
	for (int i = 1; i <= n[who]; ++i)
		if (!used[who][i] && (x == 26 || x == a[who][i][0])) {
			used[who][i] = 1;
			int t1 = w1, t2 = w2;
			if (who == 0) t1 = w1 | (1 << (i - 1));
			else t2 = w2 | (1 << (i - 1));
			if (!dfs(who ^ 1, a[who][i][1], t1, t2)) {
				used[who][i] = 0;
				return ans[x][w1][w2] = 1;
			}
			used[who][i] = 0;
		}
	return ans[x][w1][w2] = 0;
}
int main()
{
	int T, cs = 0;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n[0]);
		gets(s);
		for (int i = 1; i <= n[0]; ++i) {
			gets(s);
			a[0][i][0] = s[0] - 'a';
			a[0][i][1] = s[strlen(s) - 1] - 'a';
		}
		scanf("%d", &n[1]);
		gets(s);
		for (int i = 1; i <= n[1]; ++i) {
			gets(s);
			a[1][i][0] = s[0] - 'a';
			a[1][i][1] = s[strlen(s) - 1] - 'a';
		}
		bool yes = 0;
		memset(ans, -1, sizeof ans);
		yes = dfs(0, 26, 0, 0);
		/*
		for (int i = 0; i < 26; ++i)
			if (dfs(0, i)) {
				yes = 1;
				break;
			}
			*/
		printf("Game %d: ", ++cs);
		if (yes) puts("player1");
		else puts("player2");
	}
	return 0;
}
