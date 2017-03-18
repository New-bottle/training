#include <cstdio>
#include <set>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 200010;

int n, a[N], b[N];

set<int> s;
set<int>::iterator it;
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &b[i]);
		s.insert(b[i]);
	}
	int mx = 0, mn = 0;
	sort(a + 1, a + n + 1);
	for (int i = n; i; --i) {
		if (a[i] > *s.rbegin()) {
			s.erase(s.begin());
			++mn;
		} else {
			s.erase(s.lower_bound(a[i]));
		}
	}
	s.clear();
	for (int i = 1; i <= n; ++i) s.insert(b[i]);
	for (int i = 1; i <= n; ++i) {
		it = s.lower_bound(a[i]);
		if (it == s.begin()) {
			it = s.end();
			--it;
			s.erase(it);
		} else {
			--it;
			s.erase(it);
			++mx;
		}
	}
	int win = n / 2 + 1;
	if (n & 1) {
		if (mn < win && mx >= win) puts("Both");
		else if (mn >= win) puts("First");
		else if (mx < win) puts("Second");
	} else {
		if (mn == n / 2 && mx == n / 2) puts("None");
		else if (mn >= win - 1) puts("First");
		else if (mx < win) puts("Second");
		else puts("Both");
	}
	return 0;
}
/*

 9 > 1
 8 > 2
 4 < 6
 3 < 7
   */
