#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int N = 1002;
const int P = 1e9 + 7;
int f[N][N][3][3], n, m, a[N];

void add(int &x, int y){
	x += y;
	if (x >= P) x -= P;
}
int main(){
	int T;
	scanf("%d", &T);
	while(T --) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
		sort(a + 1, a + n + 1);
		for(int i = 0; i <= n; i ++)
			for(int j = 0; j <= m; j ++)
				for(int k = 0; k < 3; k ++)
					for(int l = 0; l < 3; l ++) f[i][j][k][l] = 0;
		int ans = 0;
		f[0][0][0][0] = 1;
		for(int i = 1; i <= n; i ++)
			for(int j = 0; j <= m; j ++)
				for(int k = 0; k < 3; k ++)
					for(int l = 0; l < 3; l ++) {
						if (j >= a[i]) {
							if (k) add(f[i][j][k][l], f[i - 1][j - a[i]][k - 1][l]);
							add(f[i][j][k][l], f[i - 1][j - a[i]][k][l]);
						}
						if (l) add(f[i][j][k][l], f[i - 1][j][k][l - 1]);
						add(f[i][j][k][l], f[i - 1][j][k][l]);
					}
		for(int j = 1; j <= m; j ++) if (f[n][j][2][2]) add(ans, f[n][j][2][2]);
		printf("%lld\n", (LL)ans * 4LL % P);
	}
	return 0;
}
