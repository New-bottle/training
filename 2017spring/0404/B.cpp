#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1010;
typedef long long LL;
typedef unsigned int u32;

int n, a[4][N];
u32 sm[N];
int main()
{
	int T, cs = 0;
	scanf("%d", &T);
	while (T--) {
		printf("Case %d: ", ++cs);
		scanf("%d", &n);
		for (int k = 0; k < 4; ++k)
			for (int i = 0; i < n; ++i)
				scanf("%d", &a[k][i]);
		for (int t1 = 0; t1 < n; ++t1)
			for (int t2 = 0; t2 < n; ++t2)
				for (int t3 = 0; t3 < n; ++t3)
	}
	return 0;
}
