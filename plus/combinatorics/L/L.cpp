#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int P = 1e6 + 3;
const int N = 7e5 + 10;
int n, k;
int Pow(int a, int b){
	int r = 1;
	while(b){
		if (b & 1) r = 1LL * r * a % P;
		a = 1LL * a * a % P;
		b >>= 1;
	}
	return r;
}
LL fac[N], inv[N];
LL C(int n, int m){
	return 1LL * fac[n] * inv[m] % P * inv[n - m] % P;
}
int main(){
	fac[0] = 1;
	for(int i = 1; i <= 7e5; i ++) fac[i] = fac[i - 1] * i % P;
	inv[700000] = Pow(fac[700000], P - 2); inv[0] = inv[1] = 1;
	for(int i = 7e5 - 1; i; i --) inv[i] = inv[i + 1] * (i + 1) % P;

	scanf("%d%d", &n, &k);
	int ans = 0;
	for(int i = 1; i <= n; i ++)
		ans = (ans + C(i + k - 1, k - 1)) % P;
	printf("%d\n", ans);
	return 0;
}
