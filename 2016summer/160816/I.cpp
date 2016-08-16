#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#define INF 0x3f3f3f3f
#define N 100010
using namespace std;
int n;
vector<int> edge[N];

int f[N][2];
void dfs(int u, int fa){
	if(fa == 0) f[u][0] = 0;
	else f[u][0] = 1;
	f[u][1] = 0;
	
	int mn1 = 0, mn2 = 0;
	for(int i = 0; i < (int)edge[u].size(); i ++){
		int v = edge[u][i];
		if(v == fa) continue;
		dfs(v, u);
		f[u][1] += f[v][0];
		f[u][0] += f[v][0];
		int t = f[v][1] - f[v][0];
		if(t < mn2){
			if(t < mn1){
				mn2 = mn1;
				mn1 = t;
			}
			else mn2 = t;
		}
	}
	f[u][1] = min(f[u][1], f[u][1] + mn1);
	f[u][0] = min(f[u][0], min(f[u][0] + mn1, f[u][0] + mn1 + mn2));
}
int main(){
	scanf("%d", &n);
	for(int i = 1; i < n; i ++){
		int x, y;
		scanf("%d%d", &x, &y);
		edge[x].push_back(y);
		edge[y].push_back(x);
	}
	dfs(1, 0);
	cout << f[1][0] + 1 << endl;
	return 0;
}
