#include <iostream>

typedef unsigned long long ull;

const int N = 100100;
ull mem[N];

ull f(int a)
{
	if (mem[a])
		return mem[a];
	ull ans = 0;
	for (int i = 1; i < a; ++i) {
		for (int j = 1; j < a; ++j) {
			if ((ull) i * j % a)
				++ans;
		}
	}
	return mem[a] = ans;
}

ull g(int a)
{
	ull ans = 0;
	for (int i = 1; i <= a / 2; ++i) {
		if (a % i == 0)
			ans += f(i);
	}
	ans += f(a);
	return ans;
}

int main()
{
	for (int i = 1; i <= 100000; ++i) {
		std::cout << i << '\t' << f(i) << '\n';// << '\t' << g(i) << std::endl;
	}
}
