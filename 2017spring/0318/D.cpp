#include <cstdio>
#include <set>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 200010;

struct node
{
	int x, p, id;
	bool operator < (const node &b) const 
	{
		return x < b.x;
	}
}a[N];

bool cmp (const node &a, const node &b) 
{
	return a.p < b.p;
}

set<node> s;
set<node>::iterator it, tmp;
int ans[N], n;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &a[i].x, &a[i].p);
		a[i].id = i;
	}
	sort(a + 1, a + n + 1, cmp);
//	for (int i = 1; i <= n; ++i) printf("%d %d %d\n", a[i].x, a[i].p, a[i].id);

	for (int i = n; i; --i) {
		if (s.empty()) {
			ans[a[i].id] = -1;
		} else {
			tmp = it = s.lower_bound(a[i]);
			int l, r;
			bool tag[2] = {0,0};
			l = r = a[i].x;
			if (it != s.end()) {
				r = it -> x;
				tag[1] = 1;
			}
			if (it != s.begin()) {
				--it;
				l = it -> x;
				tag[0] = 1;
			}
			if (tag[0] && tag[1]) {
				if (a[i].x - l < r - a[i].x)
					ans[a[i].id] = it -> id;
				else if (r - a[i].x < a[i].x - l)
					ans[a[i].id] = tmp -> id;
				else if (it -> p > tmp -> p)
					ans[a[i].id] = it -> id;
				else 
					ans[a[i].id] = tmp -> id;
			} else if (tag[0]) {
				ans[a[i].id] = it -> id;
			} else if (tag[1]) {
				ans[a[i].id] = tmp -> id;
			} else {
				ans[a[i].id] = -1;
			}
		}
		s.insert(a[i]);
	}
	for (int i = 1; i <= n; ++i)
		printf("%d%c", ans[i], i == n ? '\n' : ' ');
	return 0;
}
