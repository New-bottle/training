#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;


bool solve(int n, int m, int a, int b, int x, int y)
{
	if (max(a, x) <= n && b + y <= m) return 1;
	if (max(a, y) <= n && b + x <= m) return 1;
	if (max(b, x) <= n && a + y <= m) return 1;
	if (max(b, y) <= n && a + x <= m) return 1;
	if (max(a, x) <= m && b + y <= n) return 1;
	if (max(a, y) <= m && b + x <= n) return 1;
	if (max(b, x) <= m && a + y <= n) return 1;
	if (max(b, y) <= m && a + x <= n) return 1;
	return 0;
}

int main()
{
	int n, m, a, b, x, y;
	scanf("%d%d", &n, &m);
	scanf("%d%d%d%d", &a, &b, &x, &y);
	if (solve(n, m, a, b, x, y)) puts("YES");
	else puts("NO");
	return 0;
}
