#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int N = 200010;

bool have[N];
int n, a[N], p[N];
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) {
		scanf("%d", &a[i]);
		have[a[i]] = 1;
	}
	sort(a + 1, a + n + 1);
	LL now = 0, ans = 0;
	for(int i = 1; i <= 200000; i ++) if (have[i]) {
//		l = lower_bound(a + 1, a + n + 1, i) - a - 1;
//		p[0] = l;
		for(int j = 1; (LL)(j * i) <= 200000; j ++) {
			int v = j * i,
				l = lower_bound(a + 1, a + n + 1, v) - a,
				r = lower_bound(a + 1, a + n + 1, v + i) - a - 1;
//			p[j] = lower_bound(a + 1, a + n + 1, v + i) - a - 1;
			p[j] = r - l + 1;
		}
//		for(int j = (200000 / i); j; j --) p[j] -= p[j - 1];
		now = 0;
		for(int j = 1; (LL)j * i <= 200000; j ++)
			now += 1LL * p[j] * (j * i);
		ans = max(ans, now);
	}
	printf("%lld\n", ans);
	return 0;
}
