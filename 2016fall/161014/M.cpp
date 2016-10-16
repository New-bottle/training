#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#define LL long long
#define INF (1LL << 59)
#define N 1100010
#define M 1000100
using namespace std;
int n, m;
vector< pair<int, LL> > edge[N];
void init(){
	for(int i = 1; i <= n + m; i ++) edge[i].clear();
}

queue<int> q;
bool vis[N];
LL dist[2][N];
void spfa(int s, LL dist[]){
	for(int i = 1; i <= n + m; i ++){
		dist[i] = INF;
		vis[i] = 0;
	}
	dist[s] = 0;
	vis[s] = 1;
	q.push(s);
	while(!q.empty()){
		int u = q.front();
		q.pop();
		vis[u] = 0;
		int sz = edge[u].size();
		for(int i = 0; i < sz; i ++){
			int v = edge[u][i].first;
			int w = edge[u][i].second;
			if(dist[v] > dist[u] + w){
				dist[v] = dist[u] + w;
				if(!vis[v]){
					vis[v] = 1;
					q.push(v);
				}
			}
		}
	}
}
void solve(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i ++){
		int v, cnt;
		scanf("%d%d", &v, &cnt);
			int x;
		for(int j = 1; j <= cnt; j ++){
			scanf("%d", &x);
			edge[x].push_back(make_pair(n + i, v));
			edge[n + i].push_back(make_pair(x, 0));
		}
	}
	spfa(1, dist[0]);
	spfa(n, dist[1]);
	LL ans = INF - 1;
	vector<int> res;
	for(int i = 1; i <= n; i ++){
		LL tmp = max(dist[0][i], dist[1][i]);
		if(tmp < ans){
			res.clear();
			res.push_back(i);
			ans = tmp;
		}
		else if(tmp == ans){
				res.push_back(i);
		}
	}
	if(ans == INF - 1){
		puts("Evil John");
		return;
	}
	printf("%lld\n", ans);
	int sz = res.size();
	for(int i = 0; i < sz; i ++){
		printf("%d%c", res[i], (i == sz - 1 ? '\n' : ' '));
	}
}
int main(){
	int testcase;
	scanf("%d", &testcase);
	for(int i = 1; i <= testcase; i ++){
		printf("Case #%d: ", i);
		init();
		solve();
	}
	return 0;
}
