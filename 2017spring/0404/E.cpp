#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 110;

int n, k;
int sg[N];
bool vis[N];

int main()
{
	int T, cs = 0;
	scanf("%d", &T);
	while (T--) {
		printf("Case %d: ", ++cs);
		scanf("%d%d", &n, &k);
		for (int i = 0; i < k; ++i) sg[i] = 0;
		sg[k] = 1;
		for (int i = k + 1; i <= n; ++i) {
			memset(vis, 0, sizeof vis);
			for (int j = 0; j + k <= i; ++j) vis[sg[j] ^ sg[i - j - k]] = 1;
			for (int j = 0; j <= n; ++j) if (!vis[j]) {
				sg[i] = j;
				break;
			}
		}
//		for (int i = 1; i <= n; ++i) printf("%d ", sg[i]); puts("");
		if (sg[n]) puts("Winning");
		else puts("Losing");
	}
	return 0;
}
