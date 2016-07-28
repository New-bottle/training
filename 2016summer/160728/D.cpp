#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const double eps = 1e-8;
const int N = 110;
struct laptop{
	int c, t, r;
}a[N];
int n, m, v;// v = speed

bool yes[N];
bool check(double time, int num){
	memset(yes, 0, sizeof yes);
	int need = 0;
	double c, t, r;
	for(int i = 1; i <= n; i ++) 
		if (a[i].r == 0) need ++;
	if (need > num) return 0;
	for(int i = 1; i <= n; i ++) {
		c = a[i].c, t = a[i].t, r = a[i].r;
		if (r * t > time * c) yes[i] = 1;
	}
	double tmp = 0.0;
	for(int i = 1; i <= n; i ++){
		if (yes[i]) continue;
		c = a[i].c, t = a[i].t, r = a[i].r;
		tmp += (time / t * c - r) / v;
	}
//	printf("check %f %d %f\n", time, num, tmp);
	return tmp < time * num + eps;
}

void solve(){
	int ans = 0;
	double sumv = 0.0;
	for(int i = 1; i <= n; i ++)
		sumv += double(a[i].c) / a[i].t;
	ans = (int) sumv / v;
	if (sumv - v * ans > eps) ans ++;
	printf("%d\n", ans);
}

int main(){
	int cs = 0;
	while(scanf("%d%d", &n, &m) == 2 && n && m){
		printf("Case %d:\n", ++ cs);
		scanf("%d", &v);
		for(int i = 1; i <= n; i ++)
			scanf("%d%d%d", &a[i].c, &a[i].t, &a[i].r);
		solve();
		int x;
		double l, r, mid;
		for(int i = 1; i <= m; i ++){
			scanf("%d", &x);
			l = 0.0; r = 1e5 + 1;
			for(int i = 1; i <= 100; i ++){
				mid = (l + r) / 2;
				if (check(mid, x)) l = mid;
				else r = mid;
			}
			if (l + eps > 1e5) puts("-1.000");
			else printf("%.3f\n", l);
		}
	}
	return 0;
}
