#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100010;

int n;

struct Time
{
	int h, m;
	bool operator < (const Time &b) const 
	{
		if (h == b.h) return m < b.m;
		else return h < b.h;
	}
	bool operator == (const Time &b) const 
	{
		return !(*this < b) && !(b < *this);
	}
};

struct node
{
	Time st, ed;
	int id;
	bool operator < (const node &b) const {
		return ed < b.ed;
	}
}a[N];
bool cmp (const node &a, const node &b)
{
	return a.st < b.st;
}

bool yes[N];
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d:%d %d:%d", &a[i].st.h, &a[i].st.m, &a[i].ed.h, &a[i].ed.m);
		a[i].id = i;
	}
	sort (a + 1, a + n + 1);
	Time now = Time();
	for (int i = 1; i <= n; ++i)
		if (now < a[i].st || now == a[i].st) {
			yes[a[i].id] = 1;
			now = a[i].ed;
		}
	sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; ++i) if (yes[a[i].id]) printf("%d ", a[i].id);
	return 0;
}
