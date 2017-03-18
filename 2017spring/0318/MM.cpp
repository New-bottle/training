#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 200010;

int k, n, num[26], ans[N];
char s[N];

int main()
{
	scanf("%d", &k);
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for (int i = 1; i <= n; ++i) {
		int now = 0;
		memset(num, 0, sizeof num);
		ans[i] = 1e9;
		for (int j = i; j > 0; --j) {
			++num[s[j] - 'a'];
			if (num[s[j] - 'a'] == 1) ++now;
			if (now == k) {
				if (ans[j - 1] != -1) {
					ans[i] = min(ans[i], ans[j - 1] + 1);
				}
				else if (ans[i] == 0) ans[i] = -1;
			}
			if (now > k) break;
		}
		if (now < k) ans[i] = -1;
		printf("%d%c", ans[i], i == n ? '\n' : ' ');
	}
	return 0;
}
