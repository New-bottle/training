#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;
int n, k, a[102];
int f[2][102][10][(1<<8) + 2];
void update(int &x, int y){
	x = min(x, y);
}
int main(){
	int T = 0;
	while(scanf("%d%d", &n, &k) == 2 && n + k){
		int all = 0;
		for(int i = 1; i <= n; i ++){
			scanf("%d", &a[i]);
			a[i] -= 25;
			all |= (1 << a[i]);
		}
//		for(int i = 1; i <= n; i ++) printf("%d ",a[i]); puts("");
		memset(f, INF, sizeof f);
		f[0][0][0][0] = 0;
		for(int i = 0; i < n; i ++){
			int now = i & 1;
			memset(f[now ^ 1], 0x3f, sizeof f[now ^ 1]);
			for(int j = 0; j <= k; j ++)
				for(int l = 0; l <= 7; l ++)
					for(int s = 0; s < (1 << 8); s ++) if (f[now][j][l][s] != INF){
//						printf("%d %d %d %d = %d\n",i,j,l,s,f[now][j][l][s]);
						update(f[now ^ 1][j + 1][l][s], f[now][j][l][s]);
						if (s) update(f[now ^ 1][j][a[i + 1]][s | (1 << a[i + 1])], f[now][j][l][s] + (l != a[i + 1]));
						else   update(f[now ^ 1][j][a[i + 1]][s | (1 << a[i + 1])], f[now][j][l][s] + 1);
					}
		}
		int ans = INF;
		for(int j = 0; j <= k; j ++)
			for(int l = 0; l <= 7; l ++)
				for(int s = 0; s < (1 << 8); s ++){
					if (s ^ all) f[n & 1][j][l][s] += __builtin_popcount(s ^ all);
					ans = min(ans, f[n & 1][j][l][s]);
				}
		printf("Case %d: %d\n\n", ++ T, ans);
	}
	return 0;
}
