#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 2e5 + 10;
typedef long long LL;

int n, m, a[N];
int f[N][20];

void ready()
{
	for (int i = 1; i <= n; ++i) f[i][0] = i;
	for (int j = 1; (1 << j) <= n; ++j)
		for (int i = 1; (i + (1 << j) - 1) <= n; ++i) {
			int l = f[i][j - 1], r = f[i + (1 << (j - 1))][j - 1];
			if (a[l] < a[r]) f[i][j] = l;
			else f[i][j] = r;
		}
}

int rmq(int l, int r)
{
	int k = log(r - l + 1.0) / log(2.0);
	if (a[f[l][k]] < a[f[r - (1 << k) + 1][k]]) return f[l][k];
	else return f[r - (1 << k) + 1][k];
//	return min(f[l][k], f[r - (1 << k) + 1][k]);
}

LL solve(int l, int r, int k)
{
	if (l > r) return 0;
	if (l == r) return a[l] - k;
	int mid = rmq(l, r);
//	printf("solve %d %d %d mid = %d\n", l, r, k, mid);
	return solve(l, mid - 1, a[mid]) + solve(mid + 1, r, a[mid]) + a[mid] - k;
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	ready();
	cout << solve(1, n, 0) << endl;
	return 0;
}
