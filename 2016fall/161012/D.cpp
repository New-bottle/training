#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#define LL long long
#define N 1010
using namespace std;
struct Circle{
	int x, y, r;
	friend bool is_touch(const Circle &a, const Circle &b){
		LL tmp1 = 1LL * (a.x - b.x) * (a.x - b.x) + 1LL * (a.y - b.y) * (a.y - b.y);
		LL tmp2 = 1LL * (a.r + b.r) * (a.r + b.r);
		return tmp1 == tmp2;
	}
}cir[N];
struct Answer{
	int son, mother;
	int kind;
}ans[N];
int n;
vector<int> edge[N];
bool vis[N];
int gcd(int a, int b){
	int c;
	while(b){
		c = a;
		a = b;
		b = c % b;
	}
	return a;
}
void dfs(int u, int kind){
	if(vis[u]) return;
	vis[u] = 1;
	int son = cir[1].r;
	int mother = cir[u].r;
	int g = gcd(son, mother);
	ans[u].son = son / g;
	ans[u].mother = mother / g;
	ans[u].kind = kind;
	for(int i = 0; i < edge[u].size(); i ++){
		int v = edge[u][i];
		dfs(v, kind ^ 1);
	}
}
void solve(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++){
		edge[i].clear();
		vis[i] = 0;
		ans[i].son = ans[i].mother = ans[i].kind = 0;
		
		scanf("%d%d%d", &cir[i].x, &cir[i].y, &cir[i].r);
	}
	
	for(int i = 1; i <= n; i ++){
		for(int j = i + 1; j <= n; j ++){
			if(is_touch(cir[i], cir[j])){
				edge[i].push_back(j);
				edge[j].push_back(i);
			}
		}
	}
	dfs(1, 1);
	for(int i = 1; i <= n; i ++){
		if(ans[i].son && ans[i].mother){
			if(ans[i].mother > 1) printf("%d/%d ", ans[i].son, ans[i].mother);
			else printf("%d ", ans[i].son);
			puts(ans[i].kind ? "clockwise" : "counterclockwise");
		}
		else puts("not moving");
	}
}
int main(){
	int testcase;
	scanf("%d", &testcase);
	while(testcase --){
		solve();
	}
	return 0;
}
