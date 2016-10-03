#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#define N 2010
using namespace std;
vector<int> edge[N];
bool mem[N][N];
bool vis[N];
int n, k;
int _index, mark[N];
vector<int> ans1, tmp;

vector< pair<int, int> > ans2;
void dfs(int u){
	if(vis[u]) return;
	vis[u] = 1;
	int sz = edge[u].size();
	for(int i = 0; i < sz; i ++){
		dfs(edge[u][i]);
	}
}

bool used[N];
void dfs2(int u){
	if(mark[u] == _index) return;
	if(used[u]) return;
	used[u] = 1;
	int sz = edge[u].size();
	for(int i = 0; i < sz; i ++){
		dfs2(edge[u][i]);
	}
}
int main(){
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= k; i ++){
		int cnt;
		scanf("%d", &cnt);
		for(int j = 1; j <= cnt; j ++){
			int x;
			scanf("%d", &x);
			edge[x].push_back(i);
		}
	}
	for(int i = k + 1; i <= n; i ++){
		dfs(i);
	}
	
	for(int i = 1; i <= n; i ++){
		if(!vis[i]){
			ans1.push_back(i);
		}
	}
	
	int sz = ans1.size();
	printf("%d\n", sz);
	for(int i = 0; i < sz; i ++){
		printf("%d%c", ans1[i], (i < sz - 1 ? ' ' : '\n'));
	}
	
	int Size = 0;
	for(int i = 1; i <= n; i ++){
		++ _index;
		mark[i] = _index;
		for(int j = 1; j <= n; j ++) used[j] = 0;
		for(int j = k + 1; j <= n; j ++){
			dfs2(j);
		}
		tmp.clear();
		for(int j = 1; j <= n; j ++){
			if(!used[j] && vis[j]) tmp.push_back(j);
		}
		
		int sz = tmp.size();
		for(int j = 0; j < sz; j ++){
			for(int k = j + 1; k < sz; k ++){
				if(!mem[tmp[j]][tmp[k]]){
					Size ++;
					if(Size <= 10000) ans2.push_back(make_pair(tmp[j], tmp[k]));
					mem[tmp[j]][tmp[k]] = mem[tmp[k]][tmp[j]] = 1;
				}
			}
		}
	}
	
	printf("%d\n", Size);
	if(Size > 10000) return 0;
	for(int i = 0; i < Size; i ++){
		printf("%d %d\n", ans2[i].first, ans2[i].second);	
	}
	return 0;
}
