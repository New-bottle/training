#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1000010, M = 100010;
typedef long long LL;

int n, m;
int a[N], lft[N], up[N];
LL vu[N], vl[N];
char s[M];

int main()
{
	scanf("%d%d", &n, &m);	
	for (int i = 0; i < n; ++i) {
		scanf("%s", s + 1);
		for (int j = 1; j <= m; ++j) {
			int now = i * m + j;
			if (s[j] == '.') a[now] = 1;
			else a[now] = 0;
			if (a[now]) {
				lft[now] = (j > 1 ? lft[now - 1] : 0) + 1;
				vl[lft[now] + 1] -= 1;
				++vl[1];

				up[now] = (i ? up[now - m] : 0) + 1;
				vu[up[now] + 1] -= 1;
				++vu[1];
			}
		}
	}
	LL ans = 0;
	n = max(n, m);
	for (int k = 1; k <= n; ++k) {
		vu[k] += vu[k - 1];
		vl[k] += vl[k - 1];
		ans = vu[k] + vl[k];
//		if (k == 1) ans -= vu[k];
		cout << (k == 1 ? ans / 2 : ans) << (k == n ? '\n' : ' ');
	}

	/*
	for (int i = 0; i < n; ++i) {
		for (int j = 1; j <= m; ++j) printf("%d ", lft[i * m + j]);
		puts("");
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 1; j <= m; ++j) printf("%d ", up[i * m + j]);
		puts("");
	}
	*/
	return 0;
}
