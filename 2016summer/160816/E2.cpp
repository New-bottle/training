#include <iostream>
#include <set>
#include <unordered_set>

struct H {
	size_t operator () (const std::pair<int, int>& p) const {
		return p.first + (size_t) 19961237 * p.second;
	}
};

const int N = 21;

int arr[N] = {0,
	1,
	2,
	3,
	5,
	8,
	14,
	25,
	45,
	85,
	162,
	310,
	595,
	1165,
	2285,
	4485,
	8808,
	17306,
	34302,
	68009,
	134853,
};

#if 0
void test(int n)
{
	std::unordered_set<std::pair<int, int>, H> set;
	int endv = 1 << (n - 1);
	for (int i = 1; i < endv; ++i) {
		int sum = 0;
		int cnt = __builtin_popcount(i);
		for (int j = 1; j <= n; ++j) {
			if (i & 1 << (j - 1))
				sum += arr[j];
		}
		set.emplace(cnt, sum);
	}
	//int v = arr[n - 1] + 1;
	while (1) {
		//arr[n] = v;
		auto nset = set;
		int endv = 1 << n;
		for (int i = 1 << (n - 1); i < endv; ++i) {
			int sum = 0;
			int cnt = __builtin_popcount(i);
			for (int j = 1; j <= n; ++j) {
				if (i & 1 << (j - 1))
					sum += arr[j];
			}
			if (nset.count(std::make_pair(cnt, sum))) {
				//std::cout << "CONFLICT " << cnt << ' ' << sum << '\n';
				goto fail;
			}
			nset.emplace(cnt, sum);
		}
		break;
fail:
		std::cout << "FAIL" << std::endl;
		std::exit(0);
	}
}
#endif

int main()
{
	int a;
	std::cin >> a;
	std::cout << arr[a] << std::endl;
}
