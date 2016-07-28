#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = (1 << 20) + 10;

int n, m;
double p[7][32];
long double f[N][2];
inline int getnum(int *c, int n){
	int ans = 0;
	for(int i = 0; i < n; i ++){
		ans <<= 4;
		ans += c[i];
	}
	return ans;
}
void getc(int *c, int s, int n){
	for(int i = n - 1; i >= 0; i --){
		c[i] = s & 15;
		s >>= 4;
	}
}
int c[32], num, lim;
bool yes[32], vis[N][2];
long double dfs(int x, int s, bool k){
	if (vis[s][k]) return f[s][k];
	vis[s][k] = 1;
	if (x == m + 1) return 0.0;
	getc(c, s, n);
	int now = 0;
	for(int i = 0; i < n; i ++)
		if (c[i] == lim) now ++;
	int del = (now == num), tmp;
	long double ans = 0.0;
	if (yes[x] && !k){
		for(int i = 0; i < n; i ++){
			c[i] ++;
			tmp = getnum(c, n);
			if (c[i] <= lim - del)
				ans = max(ans, 1.0 * dfs(x + 1, tmp, 0));
			c[i] --;
		}
	}else{
		for(int i = 0; i < n; i ++){
			c[i] ++;
			tmp = getnum(c, n);
			if (c[i] <= lim - del)
				ans = max(ans, p[i][x] * (dfs(x + 1, tmp, 1) + 1.0) + (1.0 - p[i][x]) * dfs(x + 1, tmp, 0));
			c[i] --;
		}
	}
	return f[s][k] = ans;
}
void init(){
	memset(yes, 0, sizeof yes);
	memset(vis, 0, sizeof vis);
	for(int i = 0; i < (1 << (n * 4)); i ++)
		for(int j = 0; j < 2; j ++) f[i][j] = 0.0;

	scanf("%d%d", &n, &m);
	lim = m / n;
	if (m % n){
		lim ++;
		num = m % n;
	}else num = n;

	int k, x;
	scanf("%d", &k);
	for(int i = 1; i <= k; i ++){
		scanf("%d", &x);
		yes[x] = 1;
	}
	for(int i = 0; i < n; i ++)
		for(int j = 1; j <= m; j ++)
			scanf("%lf", &p[i][j]);
}
int main(){
	int T, cs = 0;
	scanf("%d", &T);
	while(cs < T){
		printf("Case %d: ", ++ cs);
		init();
		printf("%.4f\n", (double)dfs(1, 0, 1));
	}
	return 0;
}
