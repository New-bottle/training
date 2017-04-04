#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100010;

typedef long long LL;
LL n, m;
LL check(LL t)
{
	if (t == -1) return 0;
	return (t + 2) * (t + 1) / 2;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int T, cs = 0;
	cin >> T;
	while (T--) {
		cout << "Case " << ++cs << ": ";
//		printf("Case %d: ", ++cs);
		cin >> n >> m;
		LL l = -1, r = n, mid, ans = -1;
		while (l <= r) {
			mid = (l + r) / 2;
			if (check(mid) < m) ans = mid, l = mid + 1;
			else r = mid - 1;
		}
		LL up = ans + 1, down = (m - check(ans) - 1);
		cout << up << ' ' << down << '\n';
	}
	return 0;
}
