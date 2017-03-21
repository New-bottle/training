#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 200010;

int n;
vector<int> in[N], out[N];

int v[N], ans[N];
inline void add (int pos, int val)
{
	for (int i = pos; i <= n; i += i & (-i)) v[i] += val;
}
inline int sum(int pos)
{
	int r = 0;
	for (int i = pos; i; i -= i & (-i)) r += v[i];
	return r;
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		int l, r;
		scanf("%d%d", &l, &r);
		in[l].push_back(i);
		out[r].push_back(i);
	}
	for (int k = 1; k <= n; ++k) {
		for (int i = 0; i < (int)in[k].size(); ++i) add(in[k][i], 1);
		int l = 1, r = n, mid, as = -1;
		while (l <= r) {
			mid = (l + r) >> 1;
			if (sum(mid) >= k) as = mid, r = mid - 1;
			else l = mid + 1;
		}
		if (as == -1 || sum(as) != k) ans[k] = -1;
		else ans[k] = as;
		for (int i = 0; i < (int)out[k].size(); ++i) add(out[k][i], -1);
	}
	for (int i = 1; i <= n; ++i) printf("%d%c", ans[i], i == n ? '\n' : ' ');
	return 0;
}
