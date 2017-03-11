#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;

LL n, m;
LL gcd(LL a, LL b) {return b ? gcd(b, a % b) : a;}
void exgcd(LL a, LL b, LL &d, LL &x, LL &y)
{
	if (!b) {d = a; x = 1; y = 0;}
	else {exgcd(b, a % b, d, y, x); y -= a / b * x;}
}

LL calc(LL n, LL m)
{
	LL d, x, y;
	exgcd(n, m, d, x, y);
	LL t = x / m;
	x = x - t * m; 
	if (x <= 0LL) {
		++t; 
		x += m;
	}
	if (!y) x += m, ++t;
	y = y - t * n;
	return n * x;
}

int main()
{
	cin >> n >> m;
	LL d = gcd(n, m), ans = n / d * m;
	if (d == 1) ans = min(ans, calc(n, m));
	if (d == 1) ans = min(ans, calc(m, n));
	if (n == 1 && m == 1) ans = 1;
	if (n == 1 || m == 1) ans = min(ans, 2LL);
	cout << ans << endl;
	return 0;
}
