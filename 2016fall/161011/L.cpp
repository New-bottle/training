#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define LL long long
#define N 60
using namespace std;
int n, m;
int h[N][N];
int maxr[N], maxc[N];
void solve(){
	LL ans = 0;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= m; j ++){
			scanf("%d", &h[i][j]);
			if(h[i][j]) ans ++;
		}
	}
	
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= m; j ++){
			if(h[i - 1][j] < h[i][j]) ans = ans - h[i - 1][j] + h[i][j];
			if(h[i][j - 1] < h[i][j]) ans = ans - h[i][j - 1] + h[i][j];
			if(h[i + 1][j] < h[i][j]) ans = ans - h[i + 1][j] + h[i][j];
			if(h[i][j + 1] < h[i][j]) ans = ans - h[i][j + 1] + h[i][j];
		}
	}
	
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= m; j ++){
			h[i][j] = 0;
		}
	}
	
	printf("%lld\n", ans);
}
int main(){	
	int testcase;
	scanf("%d", &testcase);
	while(testcase --){	
		solve();
	}
	return 0;
}
