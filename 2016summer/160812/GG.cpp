#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
//#define debug

typedef long long LL;

LL f[20][2][10010][20];
int n, m, lim[30], k, fac[7];

LL solve(int pos, bool sign, bool zero, int mask, int len){
	if (!pos) return (len > 0);
	if (!sign && f[pos][zero][mask][len] != -1) return f[pos][zero][mask][len];
	LL ans = 0;
	int t = sign ? lim[pos] : 9,
		tmp = mask,
		nxt = mask * 10 % fac[k - 1];
	bool can[10];
	for(int i = 0; i < 10; i ++) can[i] = (i <= t);
	for(int j = 1; j <= min(k - 1, len); j ++) {
		can[tmp % 10] = 0;
		tmp /= 10;
	}
	if (zero) can[0] = 1;
	for(int i = 0; i <= t; i ++)
		if (can[i])
			ans += solve(pos - 1, sign && (i == lim[pos]), zero && (i == 0), nxt + i, len + !(i == 0 && zero));
#ifdef debug
	printf("solve %d %d %d %d %d= %lld\n", pos, sign, zero, mask, len, ans);
	printf("can : ");
	for(int i = 0; i < 10; i ++)
		if (can[i]) printf("%d ", i);
	puts("");
	puts("----------------------------");
#endif
	if (!sign) f[pos][zero][mask][len] = ans;
	return ans;
}

int main(){
	fac[0] = 1;
	for(int i = 1; i <= 5; i ++) fac[i] = fac[i - 1] * 10;
	LL L, R, t1, t2;
	int len = 0;
	while(cin >> L >> R >> k){
		t1 = t2 = 0;
		L --;
		if (L == 0) {
			t1 = 0;
		} else {
			len = 0;
			while(L) {
				lim[++ len] = L % 10;
				L /= 10;
			}
			memset(f, -1, sizeof f);
			t1 = solve(len, 1, 1, 0, 0);
		}
		len = 0;
		while(R){
			lim[++ len] = R % 10;
			R /= 10;
		}
		memset(f, -1, sizeof f);
		t2 = solve(len, 1, 1, 0, 0);
//		cout << t1 << " " << t2 << endl;
		cout << t2 - t1 << endl;
	}
	return 0;
}
