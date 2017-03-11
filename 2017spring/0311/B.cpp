#include <cstdio>
#include <bitset>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 5010;
const int SIZE = N * N / 10;

int n, m, cnt;

bitset<N> a[N];
string s;

bool cmp(const bitset<N>& a, const bitset<N>& b) 
{
	for (int i = 0; i < N; ++i) if (a[i] != b[i])
		return a[i] < b[i];
	return 0;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> s;
		int num = 0;
		for (int j = 0; j < m; ++j)
			if (s[j] == '1') ++num;
		if (num >= 8 && num <= 15) a[++cnt] = (bitset<N>)s;
	}
	sort(a + 1, a + cnt + 1, cmp);
	int now = 0, mx = 0;
	bitset<N> ans;
	for (int i = 0; i < 8; ++i) ans[i] = 1;
	for (int i = 1; i <= cnt; ++i) {
		if (a[i] == a[i - 1]) ++now;
		else {
			now = 1;
		}
		if (now > mx) {
			mx = now;
			ans = a[i];
		}
	}
	for (int i = m - 1; i >= 0; --i) cout << ans[i];
	cout << endl;
	return 0;
}
