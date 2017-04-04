#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 10010;

int n, m, c, a[N], v[N];
struct node {
	int v, n;
	bool operator < (const node &b) const {
		return n > b.n;
	}
}b[N];

typedef long long LL;
LL sm[N];

int main()
{
	int T, cs = 0;
	scanf("%d", &T);
	while (T--) {
		printf("Case %d: ", ++cs);
		scanf("%d%d%d", &m, &n, &c);
		memset(a, 0, sizeof a);
		for (int i = 1; i <= m; ++i) {
			int x;
			scanf("%d", &x);
			++a[x];
		}
		for (int i = 1; i <= n; ++i) v[i] = i * i % c;
		for (int i = 1; i <= n; ++i) b[i] = (node){v[i], a[i]};
		sort(b + 1, b + n + 1);
		for (int i = 1; i <= n; ++i) sm[i] = sm[i - 1] + b[i].v;
		LL ans = 0;
		for (int i = 1; i <= n; ++i)
			ans = max(ans, sm[i] * b[i].n);
		cout << ans << endl;
	}
	return 0;
}
