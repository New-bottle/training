#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 26;
int to[N], nxt[N], head[N], cnt;
void add(int x, int y){
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
}

int c[N], a[N], fa[N], n, root, size[N], son[N];
bool vis[N];
void build(){
	memset(head, 0, sizeof head); cnt = 0;
	for(int i = 1; i <= n; i ++)
		if (a[i] != i)
			add(a[i], i);
		else root = i;
}

void dfs(int x){
	size[x] = 1;
	vis[x] = 1;
	for(int i = head[x]; i; i = nxt[i])
		if (!vis[to[i]]) {
			son[x] ++;
			dfs(to[i]);
			size[x] += size[to[i]];
		}
}

bool check() {
	memset(son, 0, sizeof son);
	memset(size, 0, sizeof size);
	memset(vis, 0, sizeof vis);
	dfs(root);
	for(int i = 1; i <= n; i ++)
		if (son[i] == 1) return 0;
	for(int i = 1; i <= n; i ++)
		if (size[i] != c[i]) return 0;
	return 1;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) scanf("%d", &c[i]);
	for(int i = 1; i <= n; i ++) if (c[i] == n) root = i;
	while(!Q.empty()){
	if (check()) puts("YES");
	else puts("NO");
	return 0;
}
