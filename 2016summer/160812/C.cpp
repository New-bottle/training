#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#define N 1000100
#define LL long long
using namespace std;
LL sum;
int n;
int a[N];
void solve(){
	int ans = 0;
	for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
	sum = 0;
	for(int i = n; i; i --){
		sum += a[i];
		if(sum >= 0){
			ans ++;
			sum = 0;
		}
	}
	printf("%d\n", ans);
}
int main(){
	while(scanf("%d", &n) == 1){
		solve();
	}
}
