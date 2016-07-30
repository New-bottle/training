#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;
int to[N << 1], nxt[N << 1], head[N], cnt;
void add(int x, int y){
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
	to[++ cnt] = x; nxt[cnt] = head[y]; head[y] = cnt;
}

int leaves, n, m, ans, size[N], child[N];
bool vis[N];
void dfs(int x){
	vis[x] = 1;
	for(int i = head[x]; i; i = nxt[i])
		if (!vis[to[i]]){
			dfs(to[i]);
			child[x] ++;
		}
	if (child[x] == 0){
		leaves ++;
		size[x] = 1;
	}
}

bool yes = 0;
int f[N][2][3];
void dp(int x){
	printf("dp %d\n", x);
	vis[x] = 1;
	if (child[x] == 0){
		f[x][0][1] = 1;
		return;
	}
	static int tmp[2][3];
	for(int i = head[x]; i; i = nxt[i])
		if (!vis[to[i]]){
			dp(to[i]);
			for(int j = 0; j < 2; j ++)
				for(int k = 1; k < 3; k ++){
					tmp[j][k] = f[x][j][k];
					f[x][j][k] = 1e9;
				}
			for(int j = 0; j < 2; j ++)
				for(int k = 0; k < 3; k ++)
					for(int tj = 0; tj < 2; tj ++)
						for(int tk = 1; tk < 3; tk ++)
							if (j + tj < 2){
								int t = k + tk;
								while (t > 2) t -= 2;
								f[x][j + tj][t] = min(f[x][j + tj][t], tmp[j][k] + f[to[i]][tj][tk] + tk);
							}
		}
	f[x][1][1] = min(f[x][1][1], f[x][0][2]);
}

int main(){
	int T;
	scanf("%d", &T);
	while(T --){
		scanf("%d", &n);
		memset(head, 0, sizeof head); cnt = 0;
		memset(child, 0, sizeof child);
		memset(size, 0, sizeof size);
//		/*
		for(int i = 1; i <= n; i ++)
			for(int j = 0; j < 2; j ++)
				for(int k = 0; k < 3; k ++) f[i][j][k] = 0;
//				*/
		int x, y;
		for(int i = 1; i < n; i ++){
			scanf("%d%d", &x, &y);
			add(x, y);
		}
		leaves = ans = 0;
		memset(vis, 0, sizeof vis);
		dfs(1);
		memset(vis, 0, sizeof vis);
		dp(1);
		for(int i = 1; i <= n; i ++)
			for(int j = 0; j < 2; j ++)
				for(int k = 0; k < 3; k ++) if (f[i][j][k]) printf("f[%d][%d][%d] = %d\n", i, j, k, f[i][j][k]);
		ans = min(f[1][leaves & 1][2], f[1][leaves & 1][1]);
		printf("%d\n", ans);
	}
	return 0;
}
