#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 52;

int sg[N][N], n, m;
char mp[N][N];

bool vis[N * N];

void init(){
	for(int i = 1; i <= 50; i ++)
		for(int j = 1; j <= 50; j ++) {
			memset(vis, 0, sizeof vis);
			for(int x = 0; x < i; x ++)
				for(int y = 0; y < j; y ++)
					vis[sg[x][j] ^ sg[i][y] ^ sg[x][y]] = 1;
			for(int x = 0; x <= 2500; x ++)
				if (!vis[x]) {
					sg[i][j] = x;
					break;
				}
		}
}

int main(){
	init();
	scanf("%d%d", &n, &m);
	int ans = 0;
	for(int i = 1; i <= n; i ++) {
		scanf("%s", mp[i] + 1);
		for(int j = 1; j <= m; j ++)
			if (mp[i][j] - '0' == 1) ans ^= sg[i][j];
	}
	puts(ans ? "Ann" : "Betty");
	if (ans) {
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++) if (mp[i][j] - '0' == 1)
				for(int x = 0; x < i; x ++)
					for(int y = 0; y < j; y ++)
						if ((ans ^ sg[i][j] ^ sg[x][j] ^ sg[i][y] ^ sg[x][y]) == 0) {
							printf("%d %d\n%d %d\n", i, j, x, y);
							return 0;
						}
	}
	return 0;
}
