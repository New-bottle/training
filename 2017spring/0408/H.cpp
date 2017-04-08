#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
int n, n1, c1, n2, c2;

int gcd(int a, int b) {return b ? gcd(b, a % b) : a;}
int main()
{
	while (scanf("%d", &n) != EOF && n) {
		scanf("%d%d%d%d", &c1, &n1, &c2, &n2);
		bool sign = 0;
		if ((LL)c1 * n2 > (LL)c2 * n1) sign = 1; //use 2 more
		int ans1 = 0, ans2 = 0, md = 0;
		if (sign) {
			ans2 = n / n2;
			ans1 = n % n2 / n1;
			md = n - ans1 * n1 - ans2 * n2;
			while (n - ans1 * n1 - ans2 * n2 > 0 && ans2) {
				--ans2;
				ans1 += (n - ans1 * n1 - ans2 * n2) / n1;
				if (n - ans1 * n1 - ans2 * n2 == md) break;
			}
			if (n - ans1 * n1 - ans2 * n2) {
				puts("failed");
				continue;
			} else printf("%d %d\n", ans1, ans2);
		} else {
			ans1 = n / n1;
			ans2 = n % n1 / n2;
			md = n - ans1 * n1 - ans2 * n2;
			while (n - ans1 * n1 - ans2 * n2 > 0 && ans1) {
				--ans1;
				ans2 += (n - ans1 * n1 - ans2 * n2) / n2;
				if (n - ans1 * n1 - ans2 * n2 == md) break;
			}
			if (n - ans1 * n1 - ans2 * n2) puts("failed");
			else printf("%d %d\n", ans1, ans2);
		}
	}
	return 0;
}
