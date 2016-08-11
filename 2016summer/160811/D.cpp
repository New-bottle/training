#include<cstdio>
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<cstring>
#define LL __int128
#define N 50100
using namespace std;
int n, k;
int a[N];
LL sum;
long double sqr(long double x){
	return x * x;
}
void solve(){
	sum = 0;
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i ++){
		scanf("%d", &a[i]);
	}
	sort(a + 1, a + n + 1);
	int l = 1, r = n - k + 1;
	long double ans;
	LL cur = 0;
	int cnt = n - k;
	if(cnt == 0){
		puts("0.00000000000000");
		return;
	}
	for(int i = l; i < r; i ++) sum += a[i];
	for(int i = l; i < r; i ++) cur = cur + (LL)a[i] * a[i] * cnt;
	cur -= sum * sum;
	ans = (long double)cur / cnt;
	
	for(; r <= n; l ++, r ++){
		int del = a[r] - a[l];
		cur = cur + (LL)cnt * del * a[l] * 2 + (LL)cnt * del * del - (LL)2 * del * sum - (LL)del * del;
		sum = sum - a[l] + a[r];
		ans = min(ans, (long double)cur / cnt);
	}
	cout << fixed << setprecision(12) << ans << endl;
}
int main(){
	int testcase;
	scanf("%d", &testcase);
	while(testcase --){
		solve();
	}
	return 0;
}
