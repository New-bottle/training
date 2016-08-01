#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int INF = 1e9;
const int N = 100;
int T,n,h[110],t[110],f[110][110];

int main(){
    while(scanf("%d", &T) == 1 && T){
		for(int i = 1; i <= T; i ++) scanf("%d", &t[i]);
        scanf("%d",&n);
		int x, y;
		for(int i = 1; i <= N; i ++) h[i] = 100;
		for(int i = 1; i <= n; i ++){
			scanf("%d%d", &x, &y);
			h[x] = min(h[x], y);
		}
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= T; j ++) f[i][j] = INF;
        f[1][1]=0;
		for(int i = 2; i <= N; i ++){
			f[i][1] = f[i - 1][T];
			for(int j = 1; j < T; j ++) f[i][1] = min(f[i][1], f[i - 1][j] + 1);
			for(int j = 2; j <= T; j ++)
				if (f[i - 1][j - 1] != INF && t[j] <= h[i])
					f[i][j] = f[i - 1][j - 1];
				else f[i][j] = INF;
		}
		/*
		for(int j = 1; j <= T; j ++){
			for(int i = 1; i <= n; i ++)
				printf("%3d ", f[i][j] == INF ? -1 : f[i][j]);
			puts("");
		}
		*/
					
		int ans = INF;
		for(int i = 1; i <= T; i ++) ans = min(ans, f[N][i]);
        printf("%d\n",ans);
    }
    return 0;
}
