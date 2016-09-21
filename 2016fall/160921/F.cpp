#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#define M 50010
#define N 51000
#define LL long long
using namespace std;
int list[N], r[N], n, m;
int x[M], y[M], w[M], f[N];
int size[N];
bool flag[M];

bool cmp(const int a, const int b){
	return w[a] < w[b];
}

int getf(int x){
	return f[x] == x ? x : f[x] = getf(f[x]);
}

void merge(int x, int y){
	if(size[x] > size[y]){
		f[y] = x;
		size[x] += size[y];
	}
	else{
		f[x] = y;
		size[y] += size[x];
	}
}

int check(){
	int res = 0, cnt = 0;
	for(int i = 1; i <= n; i ++){
		f[i] = i;
		size[i] = 1;
	}
	for(int i = 1; i <= m; i ++){
		if(flag[r[i]]) continue;
		int fx = getf(x[r[i]]);
		int fy = getf(y[r[i]]);
		if(fx == fy) continue;
		//f[fx] = fy;
		merge(fx, fy);
		res = res + w[r[i]];
		cnt ++;
		if(cnt == n - 1) break;
	}
	if (cnt != n - 1)
		return -1;
	return res;
}

void solve(){
	int sum = 0;
	scanf("%d", &m);
	for(int i = 1; i <= m; i ++){
		scanf("%d%d%d", &x[i], &y[i], &w[i]);
	}
	for(int i = 1; i <= n; i ++){
		f[i] = i;
		size[i] = 1;
	}
	
	for(int i = 1; i <= m; i ++) r[i] = i;
		
	sort(r + 1, r + m + 1, cmp);
	
	int cnt = 0;
	for(int i = 1; i <= m; i ++){
		int fx = getf(x[r[i]]);
		int fy = getf(y[r[i]]);
		if(fx == fy) continue;
		//f[fx] = fy;
		merge(fx, fy);
		list[++ cnt] = r[i];
		sum = sum + w[r[i]];
		if(cnt == n - 1) break;
	}
	
	for(int i = 1; i <= m; i ++) flag[i] = 0;
	
	int ans1 = 0, ans2 = 0;
	for(int i = 1; i <= cnt; i ++){
		flag[list[i]] = 1;
		if(check() != sum){
			ans1 ++;
			ans2 += w[list[i]];
		}
		flag[list[i]] = 0; 
	}
	
	printf("%d %d\n", ans1, ans2);
}
int main(){
	while(scanf("%d", &n) == 1){
		solve();
	}
}
