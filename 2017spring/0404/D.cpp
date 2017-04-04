#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100010;
typedef long long LL;

int n, d, c, a[N];
int main()
{
	int T, cs = 0;
	scanf("%d", &T);
	while (T--) {
		printf("Case %d: ", ++cs);
		scanf("%d%d%d", &n, &d, &c);
		LL ans = 0;
		for (int i = 1; i <= n; ++i)
			scanf("%d", &a[i]);
		sort(a + 1, a + n + 1);
		ans = (LL)d * n;
		for (int i = 1; i <= n; ++i)
			ans = min(ans, (LL)a[i] * c * i + (LL)d * (n - i));
		cout << ans << endl;
	}
	return 0;
}
