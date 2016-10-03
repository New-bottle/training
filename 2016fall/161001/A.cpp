#include <cstring>
#include <iostream>

const int N = 100;
int mat[N][N];

int n, m;
int num0, num1, num2;

bool odd()
{
	//if (m < (n - 1) / 2 * 3 - 1)
	//	return false;
	for (int i = 1; i < n; i += 2) {
		mat[i][i + 1] = num1;
		num1 += 3;
	}
	for (int i = 2; i < n; i += 2) {
		mat[i][i + 1] = num2;
		num2 += 3;
	}
	mat[n][1] = num0;
	num0 += 3;
	for (int i = 1; i <= n; i += 2) {
		for (int j = 2; j <= n; j += 2) {
			if (num1 > m && num2 > m)
				goto fini0;
			if (!mat[i][j] && !mat[j][i]) {
				if (num1 <= m) {
					mat[i][j] = num1;
					num1 += 3;
				} else {
					mat[j][i] = num2;
					num2 += 3;
				}
			}
		}
	}
fini0:
	for (int i = n; i - 2 >= 1; --i) {
		if (num0 > m)
			goto fini1;
		if (!mat[i][i - 2] && !mat[i - 2][i]) {
			mat[i - 2][i] = num0;
			num0 += 3;
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 2; j <= n; j += 2) {
			if (num0 > m)
				goto fini1;
			if (!mat[i][j] && !mat[j][i]) {
				mat[i][j] = num0;
				num0 += 3;
			}
		}
	}
fini1:
	return true;
}

bool even()
{
	//if (m < (n - 2) / 2 * 3 + 1)
	//	return false;
	for (int i = 1; i < n; i += 2) {
		mat[i][i + 1] = num1;
		num1 += 3;
	}
	for (int i = 2; i < n; i += 2) {
		mat[i][i + 1] = num2;
		num2 += 3;
	}
	mat[n][2] = num0;
	num0 += 3;
	mat[n - 1][1] = num0;
	num0 += 3;
	for (int i = 1; i <= n; i += 2) {
		for (int j = 2; j <= n; j += 2) {
			if (num1 > m && num2 > m)
				goto fini0;
			if (!mat[i][j] && !mat[j][i]) {
				if (num1 <= m) {
					mat[i][j] = num1;
					num1 += 3;
				} else {
					mat[j][i] = num2;
					num2 += 3;
				}
			}
		}
	}
fini0:
	for (int i = n; i - 2 >= 1; --i) {
		if (num0 > m)
			goto fini1;
		if (!mat[i][i - 2] && !mat[i - 2][i]) {
			mat[i - 2][i] = num0;
			num0 += 3;
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 2; j <= n; j += 2) {
			if (num0 > m)
				goto fini1;
			if (!mat[i][j] && !mat[j][i]) {
				mat[i][j] = num0;
				num0 += 3;
			}
		}
	}
fini1:
	return true;
}

void work()
{
	num0 = 3;
	num1 = 1;
	num2 = 2;
	std::cin >> n >> m;
	std::memset(mat, 0, sizeof(mat));
	bool ans;
	if (n & 1)
		ans = odd();
	else
		ans = even();
	if (!ans) {
		std::cout << "-1" << std::endl;
	} else {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (mat[i][j])
					std::cout << i << ' ' << j << ' ' << mat[i][j] << std::endl;
			}
		}
	}
}

int main()
{
	std::ios::sync_with_stdio(false);
	int T;
	std::cin >> T;
	for (int t = 1; t <= T; ++t) {
		std::cout << "Case #" << t << ":\n";
		work();
	}
}
