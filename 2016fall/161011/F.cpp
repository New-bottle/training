#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;

int a[N], f[N], n;

int lis() {
	int l = 0, r = 0, mx = 0, mid, ans;
	f[1] = a[1], mx = 1;
	for(int i = 2; i <= n; i ++) {
		l = 0, r = mx;
		while(l <= r) {
			mid = (l + r) >> 1;
			if (f[mid] <= a[i]) ans = mid, l = mid + 1;
			else r = mid - 1;
		}
		if (f[ans + 1] != -1) f[ans + 1] = min(f[ans + 1], a[i]);
		else f[ans + 1] = a[i], mx = max(mx, ans + 1);
	}
//	for(int i = 1; i <= n; i ++) printf("%d ", f[i]); puts("");
	for(int i = 0; i <= n + 1; i ++) f[i] = -1;
	return mx;
}

int main(){
	int T;
	scanf("%d", &T);
	memset(f, -1, sizeof f);
	while(T --) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
		int l1 = lis(), l2 = 0;
		reverse(a + 1, a + n + 1);
		l2 = lis();
//		printf("%d %d\n", l1, l2);
		if (l1 >= n - 1 || l2 >= n - 1) puts("YES");
		else puts("NO");
	}
	return 0;
}
