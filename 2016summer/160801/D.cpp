#include<cstdio>
#include<queue>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 20010, M = 200100;
const int INF = 1e9;
struct edge{
	int to, v;
}E[M << 1];
int head[N], nxt[N], cnt = 1;
void add(int x, int y, int z){
	E[++ cnt] = (edge){y, z}; nxt[cnt] = head[x]; head[x] = cnt;
	E[++ cnt] = (edge){x, 0}; nxt[cnt] = head[y]; head[y] = cnt;
}
int S, T, d[N], cur[N];
queue<int>Q;
bool mklevel(){
	for(int i = 0; i <= T; i ++) d[i] = -1;
	d[S] = 0;
	Q.push(S);
	while(!Q.empty()){
		int x = Q.front(); Q.pop();
		for(int i = head[x]; i; i = nxt[i])
			if (d[E[i].to] == -1 && E[i].v){
				d[E[i].to] = d[x] + 1;
				Q.push(E[i].to);
			}
	}
	return d[T] != -1;
}
int dfs(int x, int a){
	if (x == T || a == 0) return a;
	int flow = 0;
	for(int &i = cur[x]; i; i = nxt[i])
		if (d[E[i].to] == d[x] + 1 && E[i].v){
			int f = dfs(E[i].to, min(a - flow, E[i].v));
			E[i].v -= f;
			E[i ^ 1].v += f;
			flow += f;
			if (a == flow) break;
		}
	if (!flow) d[x] = -1;
	return flow;
}
int Dinic(){
	int ans = 0;
	while(mklevel()){
		for(int i = 0; i <= T; i ++) cur[i] = head[i];
		ans += dfs(S, INF);
	}
	return ans;
}
int main(){
	int H, W, C, M, nW, nC, nM, n, x;
	while(scanf("%d%d%d%d%d%d%d", &H, &W, &C, &M, &nW, &nC, &nM) == 7){
		memset(head, 0, sizeof head); cnt = 1;
		if (H < 0) break;
		for(int i = 1; i <= H; i ++) add(i, H + i, 1);
		int now = H * 2;
		for(int i = 1; i <= W; i ++) add(now + i, now + W + i, 1);
		now += W * 2;
		for(int i = 1; i <= C; i ++) add(now + i, now + C + i, 1);
		now += C * 2;
		for(int i = 1; i <= M; i ++) add(now + i, now + M + i, 1);
		now += M * 2;
		S = 0; T = now + 7;
		add(now + 1, now + 2, nW);
		add(now + 3, now + 4, nC);
		add(now + 5, now + 6, nM);
		for(int i = 1; i <= H; i ++){
			add(S, i, 1);
			add(H + i, now + 1, 1); 
		}
		for(int i = 1; i <= W; i ++) add(H * 2 + W + i, now + 3, 1);
		for(int i = 1; i <= C; i ++){
			add(now + 2, H * 2 + W * 2 + i, 1);
			add(H * 2 + W * 2 + C + i, now + 5, 1);
		}
		for(int i = 1; i <= M; i ++) add(now + 4, H * 2 + W * 2 + C * 2 + i, 1);
		add(now + 6, T, INF);
		for(int i = 1; i <= W; i ++){
			scanf("%d", &n);
			for(int j = 1; j <= n; j ++){
				scanf("%d", &x);
				add(H + x, H * 2 + i, 1);
			}
		}
		for(int i = 1; i <= C; i ++){
			scanf("%d", &n);
			for(int j = 1; j <= n; j ++){
				scanf("%d", &x);
				add(H * 2 + W + x, H * 2 + W * 2 + i, 1);
			}
		}
		for(int i = 1; i <= M; i ++){
			scanf("%d", &n);
			for(int j = 1; j <= n; j ++){
				scanf("%d", &x);
				add(H * 2 + W * 2 + C + x, H * 2 + W * 2 + C * 2 + i, 1);
			}
			add(H * 2 + W * 2 + C * 2 + M + i, T, 1);
		}
		printf("%d\n", Dinic());
	}
	return 0;
}
