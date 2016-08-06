#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 210;
const int P = 1e9 + 7;
int n, m;
int f[N][N];
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d%d", &n, &m);
	for(int j = 1; j <= m; j ++)
		f[1][j] = 1;
	for(int i = 2; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			for(int k = 1; k < j; k ++) f[i][j] = (f[i][j] + f[i - 1][k]) % P;
	int ans = 0;
	for(int j = 1; j <= m; j ++)
		ans = (ans + f[n][j]) % P;
	printf("%d\n", ans);
	return 0;
}
