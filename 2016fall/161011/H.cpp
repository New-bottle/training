#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 2050;

int n, dp[N * 2][N], f[N];

int main() {
	int T;
	scanf("%d", &T);
	while(T --) {
		scanf("%d", &n);
		for(int i = 1; i < n; i ++)
			scanf("%d", &f[i]);
		memset(dp, 0, sizeof dp);
		dp[2][1] = 2 * f[1];
		for(int i = 1; i < n; i ++)
			for(int j = 1; j < n - 1; j ++) if (dp[i][j]) {
				dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] - f[j] + f[j + 1] + f[1]);
				dp[i + 1][2] = max(dp[i + 1][2], dp[i][j] + f[2]);
			}
		int ans = 0;
		for(int j = 1; j < n; j ++) ans = max(ans, dp[n][j]);
		printf("%d\n", ans);
	}
	return 0;
}
