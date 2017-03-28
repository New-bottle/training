#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1010;
typedef long long LL;

int a[N][N], n, mre[N], lss[N];
LL s[N], b[N][N];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			scanf("%d", &a[i][j]);
			s[i] += a[i][j];
			s[j] -= a[i][j];
		}

	int cm = 0, cl = 0;
	for (int i = 1; i <= n; ++i)
		if (s[i] > 0) mre[cm++] = i;
		else if (s[i] < 0) lss[cl++] = i;
	int j = 0;
	LL x;
	for (int i = 0; i < cm; ++i) {
		while (s[mre[i]] > 0) {
			x = min(s[mre[i]], -s[lss[j]]);
			b[mre[i]][lss[j]] = x;
			s[mre[i]] -= x;
			s[lss[j]] += x;
			if (s[lss[j]] == 0) {
				if (j < cl - 1) ++j;
				else break;
			}
		}
		if (s[lss[j]] == 0 && j == cl - 1) break;
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) printf("%lld%c", b[i][j], j == n ? '\n' : ' ');
	return 0;
}
