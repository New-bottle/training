#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100;
typedef long long LL;

LL a[N], x0, ans[N], r;
int n;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin >> T;
	while (T--)
	{
		cin >> n >> x0;
		for (int i = 0; i <= n; ++i) cin >> a[i];

		LL tmp = 0;
		for (int i = n; i; --i){
			tmp = tmp * x0 + a[i];
			ans[i - 1] = tmp;
		}
		r = a[0] + x0 * ans[0];
		cout << r << "\n";
		for (int i = 0; i <= n - 1; ++i) 
			cout << ans[i] << ((i == n - 1) ? '\n' : ' ');
	}
	return 0;
}
