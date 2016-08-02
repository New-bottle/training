#include<cstdio>
#include<queue>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 10010;
int pre[N], num[N], n, m, a[N], ans[N];
bool vis[N], can[20];
queue<int>Q;

void bfs(){
	while(!Q.empty()){
		int x = Q.front(), y; Q.pop();
		for(int i = 0; i < 10; i ++) if (can[i]){
			y = (x * 10 + i) % n;
			if (!vis[y]){
				vis[y] = 1;
				Q.push(y);
				num[y] = i;
				pre[y] = x;
				if (!y) return;
			}
		}
	}
}
int main(){
	int cs = 0;
	while(scanf("%d%d", &n, &m) == 2 && n){
		printf("Case %d: ", ++ cs);
		for(int i = 0; i < 10; i ++) can[i] = 1;
		for(int i = 1; i <= m; i ++){
			scanf("%d", &a[i]);
			can[a[i]] = 0;
		}
		while(!Q.empty()) Q.pop();
		memset(vis, 0, sizeof vis);
		memset(pre, 0, sizeof pre);
		memset(num, 0, sizeof num);
		for(int i = 1; i <= 9; i ++){
			int t = i % n;
			if (can[i] && !vis[t]){
				vis[t] = 1;
				Q.push(t);
				num[t] = i;
				pre[t] = 0;
			}
		}
		bfs();
		if (!vis[0]) {
			puts("-1");
			continue;
		}
		int cnt = 0;
		int tmp = 0;
		while (pre[tmp]) {
			ans[++ cnt] = num[tmp];
			tmp = pre[tmp];
		}
		ans[++ cnt] = num[tmp];
		for(int i = cnt; i; i --) printf("%d", ans[i]);
		puts("");
	}
	return 0;
}
