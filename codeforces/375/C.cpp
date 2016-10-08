#include<cstdio>
#include<deque>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 4010;

int n, m, a[N], cnt[N], v[N];
typedef pair<int, int> pii;
deque<pii >can;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++) {
		scanf("%d", &a[i]);
		v[i] = a[i];
	}
	for(int i = 1; i <= m; i ++) v[n + i] = i;
	sort(v + 1, v + n + m + 1);
	int len = unique(v + 1, v + n + m + 1) - v - 1;
	for(int i = 1; i <= n; i ++) a[i] = lower_bound(v + 1, v + len + 1, a[i]) - v;

	int num = n / m;
	printf("%d ", num);

	for(int i = 1; i <= n; i ++) {
		if (a[i] <= m) cnt[a[i]] ++;
		else can.push_back(make_pair(a[i], i));
		if (cnt[a[i]] > num) can.push_back(make_pair(a[i], i));
	}
	sort(can.begin(), can.end());
	int sum = 0;
	for(int i = 1; i <= m; i ++) {
		while(cnt[i] < num) {
			int t = can.back().second;
			can.pop_back();
			a[t] = i;
			sum ++;
			cnt[i] ++;
		}
	}
	printf("%d\n", sum);
	for(int i = 1; i <= n; i ++) printf("%d%c", v[a[i]], i == n ? '\n' : ' ');
	return 0;
}
