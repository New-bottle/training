#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100010;
typedef long long LL;
struct Poi
{
	int x, y;
}p[N];
Poi operator - (const Poi &a, const Poi &b)
{
	return (Poi){a.x - b.x, a.y - b.y};
}
int n;
LL Cross(const Poi& a, const Poi& b)
{
	return 1LL * a.x * b.y - 1LL * a.y * b.x;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d%d", &p[i].x, &p[i].y);
	p[0] = p[n]; p[n + 1] = p[1];
	LL tmp = 0;
	for (int i = 2; i <= n; ++i)
		tmp += Cross(p[i] - p[1], p[i - 1] - p[1]);
//	cout << tmp << endl;
	if (tmp < 0) {
		reverse(p + 1, p + n + 1);
		swap(p[0], p[n + 1]);
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
//		printf("%d %d\n", p[i].x, p[i].y);
		if (Cross(p[i] - p[i - 1], p[i + 1] - p[i]) >= 0) ++ans;
	}
	printf("%d\n", ans);
	return 0;
}
