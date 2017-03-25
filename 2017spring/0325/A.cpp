#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 200010;

int n, a[N];

int main()
{
	scanf("%d", &n);
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		ans = max(ans, a[i]);
	}
	printf("%d\n", ans);
	return 0;
}
