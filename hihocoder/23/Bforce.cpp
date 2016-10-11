#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 20026;

char s[N];
int n, ans[N], f[N];

int main() {
	scanf("%d", &n);
	scanf("%s", s);
	for(int i = 0; i < (1 << n); i ++) f[i] = (s[i] == '1');
	for(int i = 0; i < (1 << n); i ++) {
		if (i > 10) {
			bool sign = 1;
			for(int t = 1; t < 10; t ++)
				if (ans[i - t] != 1) {
					sign = 0;
					break;
				}
			if (sign) {
				ans[i] = 1;
				continue;
			}
		}

		ans[i] = n;
		for(int mask = 1; mask < (1 << n); mask ++) {
			int num = __builtin_popcount(mask);
			bool yes = 1;
			for(int k = 0; k < (1 << n); k ++)
				if (((i & mask) == (k & mask)) && (f[i] != f[k])) {
					yes = 0;
					break;
				}
			if (yes) {
//				printf("i = %d mask = %d\n", i, mask);
				ans[i] = min(ans[i], num);
			}
		}
	}
	for(int i = 0; i < (1 << n); i ++) printf("%d ", ans[i]);
	puts("");
	return 0;
}
