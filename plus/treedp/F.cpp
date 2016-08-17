#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int N = 100010;
int to[N << 1], nxt[N << 1], head[N], cnt;
void add(int x, int y) {
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
	to[++ cnt] = x; nxt[cnt] = head[y]; head[y] = cnt;
}

int n, k[N], root;
bool vis[N];
LL f[N];
vector<LL>g[N];

void dfs(int x, int fa) {
	vis[x] = 1;
	f[x] = 0;
	for(int i = head[x]; i; i = nxt[i])
		if (to[i] != fa) {
			dfs(to[i], x);
			g[x].push_back(f[to[i]]);
		}
	sort(g[x].rbegin(), g[x].rend());
	int now = 0;
	if (fa != -1) k[x] --;
	while(k[x] && now < g[x].size()) {
		f[x] += g[x][now] + 2;
		k[x] --;
		now ++;
	}
	for(int i = head[x]; i; i = nxt[i])
		if (to[i] != fa) {
//			printf("k[%d] = %d k[%d] = %d\n", x, k[x], to[i], k[to[i]]);
			int t = min(k[x], k[to[i]]);
			f[x] += t * 2;
			k[x] -= t;
			k[to[i]] -= t;
			if (!k[x]) break;
		}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) scanf("%d", &k[i]);
	int x, y;
	for(int i = 2; i <= n; i ++) {
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	scanf("%d", &root);
	dfs(root, -1);
//	for(int i = 1; i <= n; i ++) printf("f[%d] = %d\n", i, f[i]);
//	for(int i = 1; i <= n; i ++) printf("k[%d] = %d\n", i, k[i]);
	cout << f[root] << endl;
	return 0;
}
