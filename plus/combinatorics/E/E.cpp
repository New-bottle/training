#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int P = 1e9 + 7;
const int N = 100010;
int n, f[N], q[N], p[N], a[N];

LL Pow(LL a, int b){
	LL r = 1;
	while(b){
		if (b & 1) r = r * a % P;
		a = a * a % P;
		b >>= 1;
	}
	return r;
}
LL getans(int v){
	int tmp = sqrt(v), num = 0;
	for(int i = 1; i <= tmp; i ++)
		if (v % i == 0){
			p[++ num] = i;
			if (i != v / i) p[++ num] = v / i;
		}
	sort(p + 1, p + num + 1);
	a[n + 1] = a[n] + 1;
	int l, r, mid, pos = 0;
	for(int i = 1; i <= num; i ++)
		q[i] = lower_bound(a + 1, a + n + 2, p[i + 1]) - a - 1;
	q[num] = n;
	for(int i = num; i; i --) q[i] -= q[i - 1];
	LL ans = 1;
	for(int i = 1; i <= num; i ++){
		if (i < num) ans = ans * Pow(i, q[i]) % P;
		else ans = (ans * (Pow(i, q[i]) - Pow(i - 1, q[i]) + P) % P) % P;
	}
	/*
	printf("v = %d\n", v);
	printf("p : ");
	for(int i = 1; i <= num; i ++) printf("%d ", p[i]); puts("");
	printf("q : ");
	for(int i = 1; i <= num; i ++) printf("%d ", q[i]); puts("");
//	*/
//	printf("getans %d = %lld\n", v, ans);
	return ans;
}
int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	LL ans = 0;
	for(int i = 1; i <= a[n]; i ++)
		(ans += getans(i)) %= P;
	cout << ans << endl;
	return 0;
}
