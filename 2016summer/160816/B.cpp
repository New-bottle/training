#include <cstring>
#include <iostream>
#include <string>

std::string s;
int n;
const int N = 120;
int arr[N];

void trans()
{
	n = s.size();
	for (int i = 0; i < n; ++i)
		arr[i] = s[n - i - 1] - '0';
}

void rearrange()
{
	for (int i = 0; i < N; ++i) {
		arr[i + 1] += arr[i] / 10;
		arr[i] %= 10;
	}
	int i = N - 1;
	while (i > 0 && arr[i] == 0)
		--i;
	n = i + 1;
}

void work()
{
reborn:;
	if (n % 2) {
		arr[n] = 1;
		for (int i = 0; i < n; ++i) {
			arr[i] = 0;
		}
		++n;
		goto reborn;
#if 0
		n = n / 2 + 1;
		for (int i = 0; i < n; ++i)
			std::cout << "10";
		std::cout << '\n';
		return;
#endif
	}
	for (int i = (n - 1) / 2; i >= 0; --i) {
		if (arr[i] == arr[n - i - 1]) {
			for (int j = 0; j < i; ++j) {
				arr[j] = 0;
			}
			++arr[i];
			if (arr[i] == 10) {
				rearrange();
				goto reborn;
			}
		}
	}
	for (int i = n - 1; i >= 0; --i) {
		std::cout << (char) (arr[i] + '0');
	}
	std::cout << '\n';
}

int main()
{
	std::ios::sync_with_stdio(false);
	while (std::getline(std::cin, s) && s != "0") {
		std::memset(arr, 0, sizeof(arr));
		trans();
		++arr[0];
		rearrange();
		work();
	}
	return 0;
}
