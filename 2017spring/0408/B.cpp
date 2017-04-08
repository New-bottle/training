#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1010;

int n, m;
int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		int a, b, x[2], y[2];
		x[0] = y[0] = 1e9;
		x[1] = y[1] = -1e9;
		for (int i = 1; i <= n; ++i) 
			for (int i = 1; i <= 4; ++i) {
				scanf("%d%d", &a, &b);
				x[0] = min(x[0], a);
				x[1] = max(x[1], a);
				y[0] = min(y[0], b);
				y[1] = max(y[1], b);
			}
		cout << 1LL * (x[1] - x[0]) * (y[1] - y[0]) << endl;
	}
	return 0;
}
