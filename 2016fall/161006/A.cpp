#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#define N 200010
#define ch(x, y) (m + (x - 1) * 100 + y)
using namespace std;
vector<int> edge[N];
int n, m, cnt;
int in[N];
bool inqueue[N];
int main(){
	scanf("%d%d", &m, &n);
	for(int i = 1; i <= m; i ++){
		int k;
		scanf("%d", &k);
		for(int j = 1; j <= k; j ++){
			int s, t;
			char c[3];
			scanf("%d%s%d", &s, c, &t);
			int id = ch(s, t);
			if(strcmp(c, "<=") == 0){
				edge[i].push_back(id);
				//cout << i << ' ' << id << endl;
				in[id] ++;
			}
			else{
				edge[id].push_back(i);
				in[i] ++;
				//cout << id << ' ' << i << endl;
			}
		}
	}
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j < 100; j ++){
			edge[ch(i, j)].push_back(ch(i, j + 1));
			in[ch(i, j + 1)] ++;
		}
	}
	
	cnt = m + ch(n, 100);
	
	queue<int> q;
	for(int i = 1; i <= cnt; i ++){
		if(in[i] == 0){
			q.push(i);
			inqueue[i] = 1;
		}
	}
	
	while(!q.empty()){
		int u = q.front();
		q.pop();
		int sz = edge[u].size();
		for(int i = 0; i < sz; i ++){
			int v = edge[u][i];
			if(!-- in[v]){
				q.push(v);
				inqueue[v] = 1;
			}
		}
	}
	
	for(int i = 1; i <= cnt; i ++){
		if(!inqueue[i]){
			puts("No");
			return 0;
		}
	}
	puts("Yes");
	return 0;
}
