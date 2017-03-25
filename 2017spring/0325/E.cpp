#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 200010;

int n, l[N], r[N];

int main()
{
	scanf("%d", &n);
	int mx = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &l[i], &r[i]);
		mx = max(mx, l[i]);
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		if (l[i] <= mx && r[i] >= mx) ++ans;
	printf("%d\n", ans);
	return 0;
}
