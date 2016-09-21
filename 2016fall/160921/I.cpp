#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

#define int long long
typedef long long LL;
const int N = 160;

int n, m;
LL e[N], d[N];
LL add[N][2][2];

void solve(int num, LL fir, LL sec, int& d1, int& d2) {
	if (fir > sec) {
		if (add[num][1][1] || add[num][1][0]) {
			d1 = add[num][1][1];
			d2 = add[num][1][0];
			return;
		}
	} else {
		if (add[num][0][1] || add[num][0][0]) {
			d1 = add[num][0][1];
			d2 = add[num][0][0];
			return;
		}
	}
	if (num == n) {
		d1 = d[num]; d2 = 0;
		return;
	}
	if (fir > sec) {
		int p1 = 0, p2 = 0,
			t1 = 0, t2 = 0;
		solve(num + 1, sec, fir + e[num], p2, p1);
		p1 += d[num];
		solve(num + 1, fir - 1, sec + e[num], t1, t2);
		t2 += d[num];
		if (p1 > t1) {
			d1 = p1;
			d2 = p2;
			add[num][1][1] = d1;
			add[num][1][0] = d2;
			return;
		} else {
			d1 = t1;
			d2 = t2;
			add[num][1][1] = d1;
			add[num][1][0] = d2;
			return;
		}
	} else {
		int p1 = 0, p2 = 0;
		solve(num + 1, sec, fir + e[num], p2, p1);
		p1 += d[num];
		d1 = p1; d2 = p2;
		add[num][0][1] = d1;
		add[num][0][0] = d2;
		return;
	}
}
signed main(){
	int A, B;
	 while(scanf("%lld%lld%lld", &n, &A, &B) == 3) {
		 for(int i = 1; i <= n; i ++)
			 scanf("%lld%lld", &e[i], &d[i]);
		 memset(add, 0, sizeof add);
		 int d1 = 0, d2 = 0;
		 solve(1, A, B, d1, d2);
		 printf("%lld %lld\n", d1, d2);
	 }
	return 0;
}
