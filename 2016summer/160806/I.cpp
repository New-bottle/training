#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int INF = 1e9;
const int N = 210;
int to[N << 1], nxt[N << 1], head[N], cnt;
void add(int x, int y){
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
	to[++ cnt] = x; nxt[cnt] = head[y]; head[y] = cnt;
}

int n;
bool vis[N], b[N], c[N], yes[N];

int num , ans;
void dp(int x){
	vis[x] = 1;
	for(int i = head[x]; i; i = nxt[i])
		if (!vis[to[i]]){
			dp(to[i]);
			if (b[to[i]]) yes[x] = 1;
			if (!yes[to[i]]){
				b[x] = 1;
				yes[x] = 1;
				yes[to[i]] = 1;
			}
		}
	if (b[x]) num ++;
}


int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d", &n);
	int x, y;
	for(int i = 1; i < n; i ++){
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	ans = 1e9;
	for(int i = 1; i <= n; i ++){
		memset(vis, 0, sizeof vis);
		memset(yes, 0, sizeof yes);
		memset(b, 0, sizeof b);
		num = 0;
		dp(i);
		if (!yes[i]) {
			b[i] = 1;
			yes[i] = 1;
			num ++;
		}
//		for(int i = 1; i <= n; i ++) printf("%d ", yes[i]); puts("");
		if (num < ans){
			ans = num;
			for(int j = 1; j <= n; j ++) c[j] = b[j];
		}
	}
	for(int i = 1; i <= n; i ++) printf("%d ", c[i]); puts("");
	return 0;
}
