#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100010;

int n;
struct node{
	int c, r, id;
}a[N];

bool cmpc (const node& a, const node& b)
{
	return a.c < b.c;
}

int findc(int l, int r, int x)
//cost less or equal to x
{
	int mid, ans = -1;
	while(l <= r)
	{
		mid = (l + r) >> 1;
		if (a[mid].c <= x) ans = mid, l = mid + 1;
		else r = mid - 1;
	}
	return ans;
}

int mx[N];
int ans[N], cnt;
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &a[i].c, &a[i].r);
		a[i].id = i;
	}
	int target = a[n].c;

	int pos, now = 1;
	
	sort(a + 1, a + n + 1, cmpc);
	for (int i = 1; i <= n; ++i)
		if (a[mx[i - 1]].r < a[i].r) mx[i] = i;
		else mx[i] = mx[i - 1];

	while (now < target) {
		++cnt;
		pos = findc(1, n, now);
		if (pos < 0)
		{
			puts("No such luck");
			return 0;
		}
		ans[cnt] = a[mx[pos]].id;
		now = a[mx[pos]].r;
	}
	ans[++cnt] = n;
	printf("%d\n", cnt);
	for (int i = 1; i <= cnt; ++i) 
		printf("%d%c", ans[i], i == cnt ? '\n' : ' ' );
	return 0;
}
