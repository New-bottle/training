#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e6 + 10;

int p;
int inv[N], ans[N];

int main()
{
	scanf("%d", &p);
	for (int i = 0; i < p; ++i) ans[i] = -1;
	for (int i = 0; i < p; ++i)
		ans[1LL * i * i % p] = i;
	for (int i = 0; i < p; ++i) printf("%d%c", ans[i], i == p - 1 ? '\n' : ' ');
	return 0;
}
