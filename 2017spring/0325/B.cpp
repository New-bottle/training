#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 200010;
typedef long long LL;

struct node
{
	int a, b;
}a[N];
bool cmp(const node &a, const node &b)
{
	return a.b - a.a < b.b - b.a;
}

int n;

int main()
{
	while (scanf("%d", &n) != EOF) {
//		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d%d", &a[i].a, &a[i].b);
		sort(a + 1, a + n + 1, cmp);
		LL now = 0;
		for (int i = n; i >= 1; --i) {
			now = max(now + a[i].b, (LL)a[i].a);
	//		cout << "now = " << now << endl;
		}
		cout << now << endl;
	}
	return 0;
}
