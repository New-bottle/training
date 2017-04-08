#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 1010;
const int P = 1e9 + 7;

int Pow(int a, int b)
{
	int r = 1;
	while (b)
	{
		if (b & 1) r = (LL)r * a % P;
		a = (LL) a * a % P;
		b >>= 1;
	}
	return r;
}
int fac[20010], inv[20010];
int C(int a, int b)
{
	return (LL)fac[a] * inv[b] % P * inv[a - b] % P;
}

int main()
{
	int T;
	scanf("%d", &T);
	fac[1] = 1;
	for (int i = 2; i <= 20000; ++i)
		fac[i] = (LL)fac[i - 1] * i % P;
	inv[20000] = Pow(fac[20000], P - 2); inv[1] = inv[0] = 1;
	for (int i = 19999; i; --i) inv[i] = (LL)inv[i + 1] * (i + 1) % P;

	while (T--) {
		int n, m;
		scanf("%d%d", &n, &m);
		printf("%d\n", C(n + m, n));
	}
	return 0;
}
