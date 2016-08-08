#include<cstdio>
#include<queue>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 200010, M = 2000010;
int to[M], nxt[M], head[N], cnt;
void add(int x, int y){
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
}

int belong[N], n, m, du[N], ans;
queue<int>Q[3];

void solve1(){
	for(int x = 1; x <= n; x ++)
		for(int i = head[x]; i; i = nxt[i])
			du[to[i]] ++;
	for(int i = 1; i <= n; i ++) 
		if (du[i] == 0)
			Q[belong[i]].push(i);
	int num = 0;
	while(num < n){
		while(!Q[1].empty()){
			int x = Q[1].front(); Q[1].pop();
			num ++;
			for(int i = head[x]; i; i = nxt[i]){
				du[to[i]] --;
				if (du[to[i]] == 0)
					Q[belong[to[i]]].push(to[i]);
			}
		}
		if (!Q[2].empty()){
			ans ++;
			while(!Q[2].empty()){
				int x = Q[2].front(); Q[2].pop();
				num ++;
				for(int i = head[x]; i; i = nxt[i]){
					du[to[i]] --;
					if (du[to[i]] == 0)
						Q[belong[to[i]]].push(to[i]);
				}
			}
			if (!Q[1].empty()) ans ++;
		}
	}
}
void solve2(){
	for(int x = 1; x <= n; x ++)
		for(int i = head[x]; i; i = nxt[i])
			du[to[i]] ++;
	for(int i = 1; i <= n; i ++) 
		if (du[i] == 0)
			Q[belong[i]].push(i);
	int num = 0;
	while(num < n){
		while(!Q[2].empty()){
			int x = Q[2].front(); Q[2].pop();
			num ++;
			for(int i = head[x]; i; i = nxt[i]){
				du[to[i]] --;
				if (du[to[i]] == 0)
					Q[belong[to[i]]].push(to[i]);
			}
		}
		if (!Q[1].empty()){
			ans ++;
			while(!Q[1].empty()){
				int x = Q[1].front(); Q[1].pop();
				num ++;
				for(int i = head[x]; i; i = nxt[i]){
					du[to[i]] --;
					if (du[to[i]] == 0)
						Q[belong[to[i]]].push(to[i]);
				}
			}
			if (!Q[2].empty()) ans ++;
		}
	}
}

int main(){
	int T;
	scanf("%d", &T);
	while(T --){
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i ++) head[i] = 0;
		cnt = 0;
//		memset(head, 0, sizeof head); cnt = 0;
		for(int i = 1; i <= n; i ++) scanf("%d", &belong[i]);
		int x, y;
		for(int i = 1; i <= m; i ++){
			scanf("%d%d", &x, &y);
			add(x, y);
		}
		ans = 0;
		solve1();
		int tmp = ans;
		ans = 0;
		solve2();
		tmp = min(tmp, ans);
		printf("%d\n", tmp);
	}
	return 0;
}
