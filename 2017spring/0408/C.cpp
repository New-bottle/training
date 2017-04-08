#include <cstdio>
#include <queue>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e6 + 10;
typedef long long LL;

int n, m, a[N], c[N], num[N];
bool ans[N];
struct node
{
	LL v, num;
	bool operator < (const node &b) const {
		return v * num < b.v * b.num || 
			(v * num == b.v * b.num && v < b.v);
	}
};

int main()
{
	int T;
	scanf("%d", &T);
	while (T --) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= 1e6; ++i) ans[i] = num[i] = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			++num[a[i]];
		}
		priority_queue<node>Q;
		for (int i = 1; i <= 1e6; ++i)
			if (num[i])
				Q.push((node){i, num[i]});

		LL now = 0;
		while (now < m && !Q.empty()) {
//			printf("top = %d %d\n", Q.top().v, Q.top().num);
			now += Q.top().v * Q.top().num;
			ans[Q.top().v] = 1;
			Q.pop();
		}
		while(!Q.empty()) Q.pop();
		if (now < m) {
			puts("Impossible");
			continue;
		}
		for (int i = 1; i <= 1e6; ++i) if (ans[i]) printf("%d ", i);
		puts("");
	}
	return 0;
}
