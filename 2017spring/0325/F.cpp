#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 1e9 + 10;
const int N = 200010;

struct node
{
	int x, y, z, id;
}a[N];

bool cmpx(const node &a, const node &b)
{
	return a.x > b.x;
}
bool cmpy(const node &a, const node &b)
{
	return a.y > b.y;
}

int n, m, mn[N];
bool win[N];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].z);
		a[i].id = i;
	}
	sort(a + 1, a + n + 1, cmpx);
	for (int i = 1; i <= n + 1; ++i) mn[i] = INF;
	for (int i = n; i; --i)
		mn[i] = min(mn[i + 1], a[i].y);
	for (int i = 1; i < n; ++i)
		if (a[i].y > mn[i + 1]) win[a[i].id] = 1;

	for (int i = 1; i <= n + 1; ++i) mn[i] = INF;
	for (int i = n; i; --i)
		mn[i] = min(mn[i + 1], a[i].z);
	for (int i = 1; i < n; ++i)
		if (a[i].z > mn[i + 1]) win[a[i].id] = 1;

	sort(a + 1, a + n + 1, cmpy);
	for (int i = 1; i <= n + 1; ++i) mn[i] = INF;
	for (int i = n; i; --i)
		mn[i] = min(mn[i + 1], a[i].z);
	for (int i = 1; i < n; ++i)
		if (a[i].z > mn[i + 1]) win[a[i].id] = 1;
	int num = 0, ans = 0;
	for (int i = 1; i <= n; ++i)
		if (!win[i]) ++num, ans = i;
	printf("%d\n", num);
	if (num) printf("%d\n", ans);
	return 0;
}
