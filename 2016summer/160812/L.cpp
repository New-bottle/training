#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define LL __int128
#define N 50010
using namespace std;
int n, a[N];

int lowbit(int x){
	return x & -x;
}
int c[N], cnt;
void add(int x){
	for(int i = x; i <= cnt; i += lowbit(i)) c[i] ++;
}
int sum(int x){
	int res = 0;
	for(int i = x; i; i -= lowbit(i)) res += c[i];
	return res;
}

int lsh[N];

LL l[N], r[N], ll[N], rr[N];

void solve(){
	for(int i = 1; i <= n; i ++){
		scanf("%d", &a[i]);
		lsh[i] = a[i];
	}
	sort(lsh + 1, lsh + n + 1);
	cnt = unique(lsh + 1, lsh + n + 1) - lsh - 1;
	for(int i = 1; i <= n; i ++){
		a[i] = lower_bound(lsh + 1, lsh + cnt + 1, a[i]) - lsh;
	}
	
	memset(c, 0, sizeof(c));
	for(int i = n; i; i --){
		r[i] = sum(a[i] - 1);
		rr[i] = sum(cnt) - sum(a[i]);
		add(a[i]);
	}
	
	memset(c, 0, sizeof(c));
	for(int i = 1; i <= n; i ++){
		l[i] = sum(a[i] - 1);
		ll[i] = sum(cnt) - sum(a[i]);
		add(a[i]);
	}
	
	LL sum = 0, U = 0, D = 0;
	for(int i = 1; i <= n; i ++){
		U += l[i];
		D += r[i];
	}
	
	sum = U * D;
	
	for(int i = 1; i <= n; i ++){
		sum -= l[i] * r[i] + ll[i] * rr[i] + l[i] * ll[i] + r[i] * rr[i];
	}
	
	char str[50];
	int len = 0;
	while(sum){
		str[len ++] = sum % 10 + '0';
		sum /= 10;
	}
	if(len == 0){
		puts("0");
	}
	else{
		for(int i = len - 1; i >= 0; i --) putchar(str[i]);
		puts("");
	}
}


int main(){
	while(scanf("%d", &n) == 1){
		solve();
	}
	return 0;
}
