#include<cstdio>
#include<queue>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 420, M = 40010;
const int INF = 1e9;

int n, m;
struct edge {
	int to, v;
}E[M << 1];
int nxt[M << 1], head[N], cnt = 1;
void add(int x, int y, int z) {
	E[++ cnt] = (edge){y, z}; nxt[cnt] = head[x]; head[x] = cnt;
	E[++ cnt] = (edge){x, 0}; nxt[cnt] = head[y]; head[y] = cnt;
}

int S, T, d[N], cur[N];
queue<int>Q;
bool mklevel() {
	Q.push(S);
	memset(d, -1, sizeof d);
	d[S] = 0;
	while(!Q.empty()) {
		int x = Q.front(); Q.pop();
		for(int i = head[x]; i; i = nxt[i])
			if (d[E[i].to] == -1 && E[i].v) {
				d[E[i].to] = d[x] + 1;
				Q.push(E[i].to);
			}
	}
	return d[T] != -1;
}
int dfs(int x, int a) {
	if (x == T || a == 0) return a;
	int flow = 0;
	for(int &i = cur[x]; i; i = nxt[i])
		if (d[E[i].to] == d[x] + 1 && E[i].v) {
			int f = dfs(E[i].to, min(a - flow, E[i].v));
			flow += f;
			E[i].v -= f;
			E[i ^ 1].v += f;
			if (a == flow) break;
		}
	if (!flow) d[x] = -1;
	return flow;
}
int Dinic() {
	int ans = 0;
	while(mklevel()) {
		for(int i = 0; i <= T; i ++) cur[i] = head[i];
		ans += dfs(S, INF);
	}
	return ans;
}

int main(){
	scanf("%d%d", &n, &m);
	S = 0; T = n + m + 1;
	int ans = 0;
	for(int i = 1; i <= m; i ++) {
		int x;
		scanf("%d", &x);
		add(n + i, T, x);
	}
	for(int i = 1; i <= n; i ++) {
		int x, v, y;
		scanf("%d%d", &v, &x);
		ans += v;
		add(S, i, v);
		for(int j = 1; j <= x; j ++) {
			scanf("%d", &y);
			add(i, n + y, INF);
		}
	}
	printf("%d\n", ans - Dinic());
	return 0;
}
