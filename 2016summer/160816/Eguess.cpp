#include <iostream>

int arr[30] = {0,
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
};

int main()
{
	for (int i = 1; i <= 19; ++i) {
		std::cout << i << ' ' << arr[i] * 2 - arr[i + 1] << std::endl;
	}
}
