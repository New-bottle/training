#include <iostream>

int main()
{
	long long ans = 1;
	long long bns = 0;
	long long delta = 4;
	long long k;
	std::cin >> k;
	for (int i = 1; ; ++i) {
		bns += ans;
		if (k < bns) {
			std::cout << i - 1 << std::endl;
			break;
		}
		//std::cout << i << ", " << bns << std::endl;
		ans += delta;
		delta += 4;
	}
	return 0;
}
