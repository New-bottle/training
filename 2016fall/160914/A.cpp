#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int N = 14;

int getlen(LL x) {
	if (!x) return 1;
	int ans = 0;
	while(x) {
		ans ++;
		x /= 10;
	}
	return ans;
}

int main(){
	int cs = 0, a, b;
	while(scanf("%d%d", &a, &b) != EOF) {
		if (!a && !b) break;
		printf("Problem %d\n", ++ cs);
		LL ans = 1LL * a * b;
		int l = getlen(ans), l1 = getlen(a), l2 = getlen(b);
		for(int i = 1; i <= l - l1; i ++) printf(" ");
		printf("%d\n", a);
		for(int i = 1; i <= l - l2; i ++) printf(" ");
		printf("%d\n", b);
		for(int i = 1; i <= l; i ++) printf("-"); puts("");
		
		int tb = b, num = 0;
		for(int i = 1; i <= l2; i ++) {
			if (tb % 10) num ++;
			tb /= 10;
		}
		if (num > 1) {
			int num0 = 0;
			for(int i = 0; i < l2; i ++) {
				int t = (b % 10) * a, tl = getlen(t);
				b /= 10;
				if (!t) {
					num0 ++;
					continue;
				}
				for(int j = 1; j <= l - tl - i; j ++) printf(" ");
				printf("%d", t);
				for(int j = 1; j <= num0; j ++) printf("0");
//				for(int j = 1; j <= i - num0; j ++) printf(" "); puts("");
				puts("");
				num0 = 0;
			}
			for(int i = 1; i <= l; i ++) printf("-"); puts("");
		}

		printf("%lld\n", ans);
	}
	return 0;
}
