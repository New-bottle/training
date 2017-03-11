#include <cstdio>
#include <queue>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100010;

int a[N], cnt[N], v[N], n, m;
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; ++i)
		if (a[i] != a[i - 1]) {
			v[++m] = a[i];
			cnt[m] = 1;
		} else ++cnt[m];
	int ans = 0, now = n;
	for (int i = m; i; --i) {
		if (now - 1 < v[i]) now -= cnt[i];
	}
	printf("%d\n", now);
	return 0;
}
