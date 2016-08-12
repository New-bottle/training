#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#define LL long long
#define MOD 1000000007
#define N 1010
using namespace std;
LL f[N][N];
int n, m;
int a[N], b[N];
void solve(){
	for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
	for(int j = 1; j <= m; j ++) scanf("%d", &b[j]);
	for(int i = 1; i <= n; i ++) f[i][0] = 0;
	for(int j = 1; j <= m; j ++) f[0][j] = 0;
	f[0][0] = 0;
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= m; j ++){
			f[i][j] = (f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1] + f[i - 1][j - 1] * (a[i] == b[j]) + (a[i] == b[j]) + MOD) % MOD;
		}
	}
	printf("%I64d\n", f[n][m]);
}
int main(){
	while(scanf("%d%d", &n, &m) == 2){
		solve();
	}
	return 0;
}
