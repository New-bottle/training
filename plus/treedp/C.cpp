#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 3010;
int to[N << 1], nxt[N << 1], head[N], sign[N << 1], cnt;
void add(int x, int y) {
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt; sign[cnt] = 0;
	to[++ cnt] = x; nxt[cnt] = head[y]; head[y] = cnt; sign[cnt] = 1;
}

int f[N][2], n, g[N][2], cut;
//f[x][0] -> down
//f[x][1] -> up

void dfs(int x, int fa) {
//	printf("dfs %d %d\n", x, fa);
	f[x][0] = f[x][1] = 0;
	int mn = 0, sm = 0;
	for(int i = head[x]; i; i = nxt[i])
		if (to[i] != fa && to[i] != cut) {
			dfs(to[i], x);
			sm += f[to[i]][0] + sign[i];
			mn = min(mn, f[to[i]][1] + (sign[i] ^ 1) - f[to[i]][0] - sign[i]);
		}
	f[x][0] = sm;
	f[x][1] = sm + mn;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i < n; i ++) {
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	cut = -1;
	dfs(1, -1);
	swap(f, g);
//	for(int i = 1; i <= n; i ++) printf("%d %d\n", g[i][0], g[i][1]);
	int ans = g[1][1];
	for(int i = 1; i <= n; i ++) {
		cut = i;
		dfs(1, -1);
		ans = min(ans, g[cut][1] + f[1][1]);
	}
	printf("%d\n", ans);
	return 0;
}
