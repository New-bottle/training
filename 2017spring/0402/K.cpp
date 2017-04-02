#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 1e9;
const int N = 1010;

struct node
{
	int w, r;
	bool operator < (const node &b) const {
		return r < b.r;
		return r - w < b.r - b.w;
	}
}a[N];
int n, f[N][N];

bool used[N];
int main()
{
	int T;
	scanf("%d", &T);
	while (T --) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
			scanf("%d%d", &a[i].w, &a[i].r);
		sort(a + 1, a + n + 1);
		for (int i = 0; i <= n; ++i)
			for (int j = 0; j <= n; ++j) f[i][j] = INF;
		f[0][0] = 0;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j <= i; ++j) if (f[i][j] != INF) {
				f[i + 1][j] = min(f[i + 1][j], f[i][j]);
				if (f[i][j] <= a[i + 1].r - a[i + 1].w)
					f[i + 1][j + 1] = min(f[i][j] + a[i + 1].w, f[i + 1][j + 1]);
			}
		int ans = 0;
		for (int i = n; i; --i) if (f[n][i] != INF) {
			ans = i;
			break;
		}
		printf("%d\n", ans);
	}
	return 0;
}
