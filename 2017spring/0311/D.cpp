#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

//#define debug
const int N = 200010;
typedef long long LL;

int n, a[N], lst[N];
LL s[N], v[N];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		s[i] = s[i - 1] + a[i];
		v[i] = s[i];
	}
	v[0] = 0;
#ifdef debug
	for (int i = 1; i <= n; ++i) printf("%lld ", s[i]);
	cout << endl;
#endif
	sort(v, v + n + 1);
	int m = unique(v, v + n + 1) - v;
	for (int i = 0; i <= n; ++i)
		s[i] = lower_bound(v, v + m, s[i]) - v;
#ifdef debug
	for (int i = 1; i <= n; ++i) printf("%lld ", s[i]);
	cout << endl;
#endif
	memset(lst, -1, sizeof lst);
	int mxlen = 1e9, l = 0, len = 0;
	for (int i = 0; i <= n; ++i) {
		if (lst[s[i]] != -1) {
			if (i - lst[s[i]] < mxlen) {
				mxlen = i - lst[s[i]];
				l = lst[s[i]] + 1;
				len = i - lst[s[i]];
			}
//			printf("%d %d\n", lst[s[i]] + 1, i - lst[s[i]]);
		} 
		lst[s[i]] = i;
	}
	if (mxlen != 1e9) {
		printf("%d %d\n", l, len);
	} else printf("-1\n");
	return 0;
}
