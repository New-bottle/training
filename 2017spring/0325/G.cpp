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
	int x, y, id;
	friend bool operator < (const node &a, const node &b)
	{
		return a.y < b.y;
	}
}a[N], q[N];
bool cmp (const node &a, const node &b) 
{
	return a.x < b.x;
}
int n, m, ans[N];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &q[i].x, &q[i].y);
		q[i].id = i;
	}
	sort(q + 1, q + n + 1, cmp);

	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &a[i].x, &a[i].y);
		a[i].id = i;
	}
	sort(a + 1, a + m + 1, cmp);

	typedef pair<int,int> pii;
	set<pii> s;
	set<pii>::iterator it;
	for (int i = n, j = m; i; --i) {
		while (j && a[j].x >= q[i].x) {
			s.insert(make_pair(a[j].y, a[j].id));
			--j;
		}
		if (s.empty()) {
			puts("-1");
			return 0;
		}
		it = s.lower_bound(make_pair(q[i].y, 0));
		if (it == s.end()) {
			puts("-1");
			return 0;
		}
		ans[q[i].id] = it -> second;
		s.erase(it);
	}
	for (int i = 1; i <= n; ++i) 
		printf("%d%c", ans[i], i == n ? '\n' : ' ');
	return 0;
}
