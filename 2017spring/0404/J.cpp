#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100;

int main()
{
	int T;
	int cs = 0;
	scanf("%d", &T);
	int h1, m1, h2, m2;
	while (T --) {
		scanf("%d%d%d%d", &h1, &m1, &h2, &m2);
		int ans = 0;
		if (h2 > h1 || (h2 == h1 && m2 >= m1)) {
			ans += (h2 - h1) * 60;
			ans -= m1;
			ans += m2;
		} else if (h2 < h1 || (h2 == h1 && m2 < m1)) {
			ans += (24 - h1 + h2) * 60;
			ans -= m1;
			ans += m2;
		}
		printf("Case %d: %d\n", ++cs, ans);
	}
	return 0;
}
