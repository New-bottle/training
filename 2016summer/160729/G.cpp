#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;
int to[N << 1], nxt[N << 1], head[N], cnt;
void add(int x, int y){
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
	to[++ cnt] = x; nxt[cnt] = head[y]; head[y] = cnt;
}


struct treasure{
	int key, chest, val;
}a[N];
int st[N], ed[N], n, m, dfs_clock, dep[N], fa[N][20];

int LCA(int x, int y){
	if (dep[x] < dep[y]) swap(x, y);
	int t = dep[x] - dep[y];
	for(int i = 0; i < 20; i ++) if (t >> i & 1) x = fa[x][i];
	for(int i = 19; i >= 0; i --)
		if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	if (x == y) return x;
	return fa[x][0];
}

void dfs(int x){
	st[x] = ++ dfs_clock;
	for(int i = 1; (1 << i) <= dep[x]; i ++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for(int i = head[x]; i; i = nxt[i])
		if (st[to[i]] == 0){
			dep[to[i]] = dep[x] + 1;
			fa[to[i]][0] = x;
			dfs(to[i]);
		}
	ed[x] = dfs_clock;
}

int main(){
	int T, cs = 0;
	scanf("%d", &T);
	while(cs < T){
		printf("Case #%d: ", ++ cs);

		memset(head, 0, sizeof head);
		cnt = dfs_clock = 0;
		scanf("%d%d", &n, &m);
		int x, y, z;
		for(int i = 1; i < n; i ++){
			scanf("%d%d", &x, &y);
			add(x, y);
		}
		dfs(1);
		for(int i = 1; i <= m; i ++){
			scanf("%d%d%d", &a[i].key, &a[i].chest, &a[i].val);
			lca = LCA(a[i].key, a[i].chest);
			if (a[i].key == a[i].chest){
				
			}else if (a[i].key == lca || a[i].chest == lca){
			}else{
		}
	}
	return 0;
}
