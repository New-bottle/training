#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int N = 1010;
LL a[N][N];
int n, m;
inline int lowbit(int x) {return x & (-x);}

int t[N << 2][N << 2];

void maintain(int o, int l, int r) {
}
void add(int x, int y, LL v) {
	if (!x || !y) return;
	for(int i = x; i <= n; i += lowbit(i))
		for(int j = y; j <= n; j += lowbit(j)) {
			a[i][j] ^= v;
			printf("a[%d][%d] ^= %lld == %lld\n", i, j, v, a[i][j]);
		}
}
LL sum(int x, int y) {
	if (!x || !y) return 0;
	LL r = 0;
	for(int i = x; i; i -= lowbit(i))
		for(int j = y; j; j -= lowbit(j))
			r ^= a[i][j];
	return r;
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i ++) {
		int opt = 0, x0, y0, x1, y1;
		scanf("%d%d%d%d%d", &opt, &x0, &y0, &x1, &y1);
		if (opt == 2) {
			LL v;
			scanf("%lld", &v);
			add(x0 - 1, y0 - 1, v);
			add(x0 - 1, y1, v);
			add(x1, y0 - 1, v);
			add(x1, y1, v);
		} else {
			LL v = 0;
			v ^= sum(x1, y1);
			v ^= sum(x0 - 1, y1);
			v ^= sum(x1, y0 - 1);
			v ^= sum(x0 - 1, y0 - 1);
			printf("%lld\n", v);
		}
	}
	return 0;
}
