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

int ch[N * 30][2], dep[N * 30], num[N * 30], tot = 1;
void ins(int v){
	int x = 1, y;
	for(int i = 17; i >= 0; i --) {
		y = v & 1;
		if (!ch[x][y]) ch[x][y] = ++ tot;
		++ num[x];
		x = ch[x][y];
		dep[x] = i;
	}
	++ num[x];
}
void rebuild(){
	for(int i = 1; i <= tot; i ++) ch[i][0] = ch[i][1] = 0;
	for(int i = 1; i <= tot; i ++) num[i] = 0;
	tot = 1;
}
int findans(int x){
	int ans = 0;
	if (num[ch[x][0]] + num[ch[x][1]] == 1) return 0;
	if (num[ch[x][0]] == 1 && num[ch[x][1]] == 1) {
		int p0 = ch[x][0], p1 = ch[x][1], s0, s1;
		ans += dep[p0];
		for(int i = dep[p0] - 1; i >= 0; i --) {
			if (ch[p0][0]) s0 = 0; else s0 = 1;
			if (ch[p1][0]) s1 = 0; else s1 = 1;
			ans += (s0 ^ s1) * dep[p0];
			p0 = ch[p0][s0]; p1 = ch[p1][s1];
		}
	}
	if (num[ch[x][0]] == 1 && num[ch[x][1]]
	return ans;
}

int size[N], son[N], st[N], ed[N], dfs_clock, v[N];
bool vis[N];
void dfs(int x){
	st[x] = ++ dfs_clock;
	v[dfs_clock] = w[x];
	vis[x] = 1;
	size[x] = 1; son[x] = 0;
	for(int i = head[x]; i; i = nxt[i])
		if (!vis[to[i]]){
			dfs(to[i]);
			size[x] += size[to[i]];
			if (size[to[i]] > size[son[x]]) son[x] = to[i];
		}
	ed[x] = dfs_clock;
}
void getans(int x){
	for(int i = head[x]; i; i = nxt[i])
		if (to[i] != son[x]) {
			getans(to[i]);
			rebuild();
		}
	getans(son[x]);
	ins(w[x]);
	if (size[x] == 1) ans[x] = -1;
	else ans[x] = findans(1);
}

int a[N];
int main(){
	int T, cs = 0;
	while(cs < T){
		printf("Case #%d: ", ++ cs);
		scanf("%d", &n);
		tot = 1;
		memset(head, 0, sizeof head); cnt = 0;
		for(int i = 1; i <= n; i ++) scanf("%d", &w[i]);
		int x, y;
		for(int i = 2; i <= n; i ++){
			scanf("%d%d", &x, &y);
			add(x, y);
		}
		dfs(1);
		s
	return 0;
}
