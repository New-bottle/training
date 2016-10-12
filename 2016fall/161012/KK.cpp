#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 150010
using namespace std;
int n, k;
struct node{
	int v, c;
	friend bool operator < (const node &a, const node &b){
		return a.c < b.c;
	}
}p[N];
int ans[N];
int sum[N];
void solve(){
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i ++){
		scanf("%d%d", &p[i].v, &p[i].c);
	}
	
	if(n <= k) puts("0");
	sort(p + 1, p + n + 1);
	
	sum[0] = 0;
	for(int i = 1; i <= n; i ++){
		sum[i] = sum[i - 1] + p[i].c;
	}
	
	for(int i = 0; i <= k; i ++){
		ans[i] = -sum[i];
		int mx = -(1 << 30);
		for(int j = i + 1; j <= n; j ++){
			mx = max(mx, p[j].v - p[j].c);
		}
		ans[i] = ans[i] + mx;
	}
	
	int mn = ans[0];
	for(int i = 1; i <= k; i ++){
		mn = min(ans[i], mn);
	}
	printf("%d\n", mn);
}
int main(){
	int testcase;
	scanf("%d", &testcase);
	while(testcase --){
		solve();
	}
	return 0;
}
