#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1000010;

int a[N], n, m;
int t[N][2], tot, rt[N], id[N];
inline void Ins(int pre, int x, int k) {
	int now = rt[k] = ++tot; id[tot] = k;
	for(int i = 30; i >= 0; i --) {
		int j = (x >> i) & 1;
		t[now][j ^ 1] = t[pre][j ^ 1];
		t[now][j] = ++tot; id[tot] = k; now = tot;
		pre = t[pre][j];
	}
}
inline int ask(int l, int r, int x) {
	if (l > r) return 0;
	int ans = 0, now = rt[r];
	for(int i = 30; i >= 0; i --) {
		int j = ((x >> i) & 1) ^ 1;
		if (id[t[now][j]] >= l) ans |= 1 << i; else j ^= 1;
		now = t[now][j];
	}
	return ans;
}

int main(){
	int T;
	scanf("%d", &T);
	id[0] = -1;
	while(T --) {
		id[0] = -1;
		Ins(rt[0], 0, 0);
		scanf("%d", &n);
		for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i ++) Ins(rt[i - 1], a[i], i);
		int ans = 0;
		for(int i = 1; i <= n; i ++)
			for(int j = i + 1; j <= n; j ++) {
				int tmp = a[i] + a[j];
				ans = max(ans, ask(1, i - 1, tmp));
				ans = max(ans, ask(i + 1, j - 1, tmp));
				ans = max(ans, ask(j + 1, n, tmp));
			}
		printf("%d\n", ans);

		for(int i = 1; i <= n; i ++) rt[i] = 0;
		for(int i = 1; i <= tot; i ++) t[i][0] = t[i][1] = id[i] = 0;
		tot = 0;
	}
	return 0;
}
