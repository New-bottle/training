#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int N = 1000100;
int prime[N], cnt, t[N];
bool vis[N];
LL Pow(LL a, int b){
	LL r = 1;
	while(b){
		if (b & 1) r = r * a;
		a = a * a;
		b >>= 1;
	}
	return r;
}

int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	LL k;
	cin >> k;
	if (k == 1){
		puts("2");
		puts("1 2");
		return 0;
	}
	for(int i = 2; i <= 100000; i ++){
		if (!vis[i]){
			prime[++ cnt] = i;
			for(int j = i + i; j <= 100000; j += i) vis[j] = 1;
		}
	}
	LL now = 0;
	for(int i = 1; i <= cnt; i ++){
		while(k % prime[i] == 0){
			t[i] ++;
			k /= prime[i];
		}
		if (t[i]) {
			now += Pow(prime[i], t[i]);
		}
		if (now > 100000){
			puts("No solution");
			return 0;
		}
	}
	if (k != 1){
		puts("No solution");
		return 0;
	}
	printf("%lld\n", now);
	now = 0;
	for(int i = 1; i <= cnt; i ++) if (t[i]){
		for(int j = 1; j < Pow(prime[i], t[i]); j ++)
			printf("%lld ",now + j + 1);
		printf("%lld ", now + 1);
		now += Pow(prime[i], t[i]);
	}
	return 0;
}
