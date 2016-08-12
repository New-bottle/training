#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 2010;
int n, m;

double f[N][N];
int main(){
	n = 2000; m = 12;
	for(int i = 1; i <= n; i ++)
		for(int j = 0; j <= m + 1; j ++) f[i][j] = 1e9;
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= m; j ++)
			for(int k = 1; k <= i; k ++) 
				f[i][j] = min(f[i][j], f[k - 1][j - 1] * k / (i + 1.0) + f[i - k][j] * (i - k + 1) / (i + 1.0) + 1.0);
	}
	while(scanf("%d%d", &n, &m) == 2){
		m = min(m, 12);
		printf("%.6f\n", f[n][m]);
	}
	return 0;
}
