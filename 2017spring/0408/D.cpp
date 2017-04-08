#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1000010;
typedef long long LL;

int n, k, a[N];

bool check (LL x)
{
	int now = 0, len = 0, ans = 0;
	for (int i = 1; i <= n; ++i) {
		if ((LL)max(now, a[i]) * (len + 1) > x) {
			++ans;
			now = a[i];
			len = 1;
		} else {
			now = max(now, a[i]);
			++len;
		}
	}
	++ans;
	return ans <= k;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		LL l = 1, r = 2e10, mid, ans = -1;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			l = max(l, (LL)a[i]);
		}
		while (l <= r) {
			mid = (l + r) >> 1;
			if (check(mid)) ans = mid, r = mid - 1;
			else l = mid + 1;
		}
		cout << ans << endl;
	}
	return 0;
}
