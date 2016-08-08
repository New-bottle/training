#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = (1 << 20) + 10;
int n, mp[23][23], sm[23], ans;
bool vis[N], yes[23];

inline int lowbit(int x){return x & (-x);}
void dfs(int mask){
	if (vis[mask]) return;
	vis[mask] = 1;
	if (mask == lowbit(mask)) {
		for(int i = 0; i < n; i ++)
			if (mask >> i & 1){
				ans ++;
				yes[i + 1] = 1;
				return;
			}
	}
	/*
	int tmp = 0;
	for(int i = 0; i < n; i ++)
		if (mask >> i & 1 && sm[i] < 0)
			tmp |= (1 << i);
	*/
	for(int i = 0; i < n; i ++){
		if ((mask >> i & 1) && sm[i] > 0){
			for(int j = 0; j < n; j ++)
				if (i != j && ((mask >> j) & 1)){
					sm[j] += mp[i][j];
				}
			dfs(mask ^ (1 << i));
			for(int j = 0; j < n; j ++)
				if (i != j && ((mask >> j) & 1)){
					sm[j] -= mp[i][j];
				}
		}
	}
}

int main(){
	int T;
	scanf("%d", &T);
	while(T --){
		memset(sm, 0, sizeof sm);
		memset(yes, 0, sizeof yes);
		memset(vis, 0, sizeof vis);
		ans = 0;
		scanf("%d", &n);
		for(int i = 0; i < n; i ++)
			for(int j = 0; j < n; j ++){
				scanf("%d", &mp[i][j]);
				sm[i] += mp[i][j];
			}
		dfs((1 << n) - 1);
		//printf("%d%c", ans, ans ? ' ' : '\n');
		if (ans == 0)
			puts("0");
		int num = 0;
		for(int i = 1; i <= n; i ++)
			if (yes[i]){
				num ++;
				printf("%d%c", i, num == ans ? '\n' : ' ');
			}
	}
	return 0;
}
