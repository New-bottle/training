#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;
typedef long long LL;

int a[N], n;
char col[N][3];

LL gcd(LL a, LL b) {return b ? gcd(b, a % b) : a;}

int main(){
	int T;
	scanf("%d", &T);
	while(T --) {
		scanf("%d", &n);
		LL sb = 0, sw = 0;
		for(int i = 1; i <= n; i ++) {
			scanf("%d%s", &a[i], col[i]);
			if (col[i][0] == 'B') sb += a[i];
			else sw += a[i];
		}
		if (!sb || !sw) {
			printf("%lld\n", sb + sw);
			continue;
		}
		LL d = gcd(sb, sw);
		sb /= d; sw /= d;
//		printf("sb = %lld sw = %lld\n", sb, sw);
		LL nb = 0, nw = 0;
		int ans = 0;
		for(int i = 1; i <= n; i ++) {
			if (col[i][0] == 'W') {
				if (nb % sb == 0 && nb / sb * sw > nw && nb / sb * sw <= nw + a[i]) {
					nw = nw + a[i] - nb / sb * sw; nb = 0;
					ans ++;
				} else nw += a[i];
			} else {
				if (nw % sw == 0 && nw / sw * sb > nb && nw / sw * sb <= nb + a[i]) {
					nb = nb + a[i] - nw / sw * sb; nw = 0;
					ans ++;
				} else nb += a[i];
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
