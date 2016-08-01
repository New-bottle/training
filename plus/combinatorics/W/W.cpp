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

int n, size[N], fa[N];
bool vis[N];
typedef long long LL;
LL f[N], g[N], h[N], sum[N], ans;
void dfs(int x){
	vis[x] = 1;
	size[x] = 1;
	for(int i = head[x]; i; i = nxt[i])
		if (!vis[to[i]]){
			fa[to[i]] = x;
			dfs(to[i]);
			size[x] += size[to[i]];
		}
}

LL calc(LL x){
	return (LL)x * (x - 1) / 2;
}
void dp(int x){
	vis[x] = 1;
	LL sm = 0, tmp = 0, presize = 0;
	for(int i = head[x]; i; i = nxt[i])
		if (!vis[to[i]]){
			dp(to[i]);
			ans += calc(size[to[i]]) * sm;// son1 -> son2 || x || son3 -> son4
			sm += calc(size[to[i]]);// son1 -> son2 not x
			tmp += presize * size[to[i]]; // son1 -> x -> son2
			presize += size[to[i]];
		}
	for(int i = head[x]; i; i = nxt[i])
		if (to[i] != fa[x]){
			ans += calc(size[to[i]]) * (n - size[x]); // fa -> x
			ans += calc(size[to[i]]) * (tmp - size[to[i]] * (size[x] - size[to[i]] - 1)); // son1 -> x -> son2
			ans += calc(size[to[i]]) * (size[x] - size[to[i]] - 1); // x -> son
			ans += (n - size[x]) * size[to[i]] * (sm - calc(size[to[i]])); // fa -> x -> son
		}
}

int main(){
	scanf("%d", &n);
	int x, y;
	for(int i = 1; i < n; i ++){
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	dfs(1);
	memset(vis, 0, sizeof vis);
	dp(1);
//	for(int i = 1; i <= n; i ++) printf("f[%d] = %lld\n", i, f[i]);
	cout << ans * 2 << endl;
	return 0;
}
