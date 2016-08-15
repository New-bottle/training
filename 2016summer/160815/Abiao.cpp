#include <iostream>

int n, m;

const int modulus = 1000000007;

const int N = 100;
int choose_[N + 2][N + 2];

void initchoose()
{
	for (int i = 0; i < N; ++i)
		choose_[i][0] = choose_[i][i] = 1;
	for (int i = 2; i < N; ++i) {
		for (int j = 1; j < i; ++j) {
			choose_[i][j] = (choose_[i - 1][j - 1] + choose_[i - 1][j] % modulus);
		}
	}
}

int ans;

void dfs(int depth, int last, long long a)
{
	if (depth == m) {
		ans = (ans + a) % modulus;
		return;
	}
	for (int i = last; i <= n; ++i)
		dfs(depth + 1, i, a * choose_[i][last] % modulus);
}

void work()
{
	dfs(0, 0, 1);
}

int main()
{
	initchoose();
	for (n = 0; n < 10; ++n) {
		for (m = 2; m < 10; ++m) {
			ans = 0;
			work();
			std::cout << '(' << n << ',' << m << ") = " << ans << "\t";
		}
		std::cout << std::endl;
	}
}
