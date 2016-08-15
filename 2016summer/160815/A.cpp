#include <iostream>

typedef long long int lli;

const lli modulus = 1000000007;

lli ipow(lli a, lli p)
{
	lli ans = 1;
	if (p == 0)
		return ans;
	ans = ipow(a, p / 2);
	ans = ans * ans % modulus;
	if (p % 2)
		ans = ans * a % modulus;
	return ans;
}

lli inv(lli a)
{
	return ipow(a, modulus - 2);
}

int main()
{
	std::ios::sync_with_stdio(false);
	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i) {
		lli n, m;
		std::cin >> n >> m;
		std::cout << ((ipow(m, n + 1) - 1) * inv(m - 1)) % modulus << std::endl;
	}
	return 0;
}
