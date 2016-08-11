#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#define N 100010
using namespace std;
namespace Trie{
	int trie[N][26];
	int g[N];
	void bfs(){
		queue<int> q;
		int v, j;
		g[1] = 0;
		q.push(1);
		while(!q.empty()){
			int u = q.front();
			q.pop();
			for(int i = 0; i < 26; i ++){
				if(v = trie[u][i]){
					for(j = g[u]; j; j = g[j]) if(trie[j][i]) break;
					g[v] = j ? trie[j][i] : 1;
					q.push(v);
				}
			}	
		}
	}
}using namespace Trie;

int cnt[N];

struct Array{
	int c[N];
	void clear(){
		for(int i = 1; i <= m; i ++) c[i] = 0;
	}
	int lowbit(int x){
		return x & -x;
	}
	void add(int x){
		for(int i = x; i <= m; i += lowbit(i)) c[i] ++;
	}
	int sum(int x){
		int res = 0;
		for(int i = x; i; i -= lowbit(i)) res += c[i];
		return res;
	}
}bit;

 
namespace Graph{
	vector<int> edge[N];
	struct status{	
		vector<int> set;
		vector<int> que
	}p[N];
	
	void get_ans(int u, int pre_ans[]){
		for(int i = 0; i < set[u].size(); i ++){
			int d = set[u][i];
			if(!cnt[d] ++) bit.add(d);
		}
		
		int cur = 0;
		for(int i = 0; i < ask[u].size(); i ++){
			int d = ask[u][i];
			cur 
		}
		
	}
	
}

vector<int> query[N];
int cnt_query;

void solve(){
	for(int i = 2; i <= n; i ++){
		char str[2];
		int pnt;
		scanf("%d%c", &pnt, str);
		trie[pnt][str - 'a'] = i;
	}
	
	bfs();
	for(int i = 1; i <= n; i ++){
		if(g[i]) edge[g[i]].push_back(i);
	}
	
	int m;
	scanf("%d",  &m);
	for(int i = 1; i <= m; i ++){
		int type, k;
		scanf("%d%d", &type, &k);
		if(type == 1) cnt_query ++;
		for(int j = 1; j <= k; j ++){
			int x;
			scanf("%d", &x);
			if(type == 1){
				query[cnt_query].push_back(x);
				p[x].que.push_back(i);
			}
			else{
				p[x].ask.push_back(i);
			}
		}
	}
	
	get_ans(1, 0);
	dfs(1);
	
}

void init(){
	memset(trie, 0, sizeof(trie));
	for(int i = 1; i <= n; i ++){
		g[i] = 0;
		edge[i].clear();
		p[i].set.clear();
		p[i].que.clear();
		ans[i] = 0;
	}
	for(int i = 1; i <= cnt_query; i ++){
		query[i].clear();
	}
	for(int i = 1; i <= m; i ++) cnt[i] = 0;
	cnt_query = 0;
	bit.clear();
	
}

int main(){
	int testcase;
	while(testcase --){
		init();
		solve();
	}
	return 0;
}
