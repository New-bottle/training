#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1000010;

int n, m, v[N], num[N], a[N], cnt, s[N];

inline void add(int x, int v){
	for(;x <= n; x += x & (-x)) num[x] += v;
}
inline int sum(int x){
	int r = 0;
	for(;x;x -= x & (-x)) r += num[x];
	return r;
}
int pos[N];
void del() {
	int ed = m;
	for(int i = 1; i <= m; i ++) {
		int l = 1, r = cnt, mid, ans = -1, t;
		while(l <= r) {
			mid = (l + r) >> 1;
			t = sum(mid);
			if (t < a[i]) l = mid + 1;
			else ans = mid, r = mid - 1;
		}
		if (ans == -1) {
			ed = i - 1;
			break;
		}
//		printf("sum(%d) = %d\n", ans, sum(ans));
		v[ans] = -1;
		pos[i] = ans;
	}
//	for(int i = 1; i <= ed; i ++) printf("%d ", pos[i]); puts("");
	for(int i = 1; i <= ed; i ++)
		add(pos[i], -1);
}

void output() {
	for(int i = 1; i <= cnt; i ++)
		s[i] = sum(i);
//	for(int i = 1; i <= cnt; i ++) printf("%d ", s[i]); puts("");
	if (s[cnt] == 0) {
		puts("Poor stack!");
		return;
	}
	for(int i = 1; i <= cnt; i ++) if (s[i] > s[i - 1])
		putchar(v[i] + '0');
	puts("");
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i ++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i ++) {
		int x;
		scanf("%d", &x);
		if (x == -1) del();
		else {
			v[++ cnt] = x;
			add(cnt, 1);
		}
//		for(int i = 1; i <= n; i ++) printf("%d ", sum(i)); puts("");
	}
	output();
	return 0;
}
