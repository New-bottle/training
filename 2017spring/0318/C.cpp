#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 2e9;
const int N = 200010;

int n, a[N];

//len < mn1 + mn2
//len > mx1 - mn1
int main()
{
	int mn1 = INF, mn2 = INF, mx1 = 0, mx2 = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	for (int i = 1; i <= n; ++i) {
		if (a[i] > mx1) mx2 = mx1, mx1 = a[i];
		else if (a[i] > mx2) mx2 = a[i];
		if (a[i] < mn1) mn2 = mn1, mn1 = a[i];
		else if (a[i] < mn2) mn2 = a[i];
	}
	int l = mx1 - mn1, r = mn1 + mn2;
	if (l + 1 >= r) puts("NO");
	else {
		puts("YES");
		printf("%d\n", l + 1);
	}
	return 0;
}
