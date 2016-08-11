#include <cstring>
#include <iostream>

const int M = 60;
const int N = 120;

int dp[N][M];
int score[M][M];
int arr[N];
int n, m;

const int INF = 100000000;

void work()
{
	std::memset(dp, 0, sizeof(dp));
	if (arr[1] != -1) {
		for (int i = 1; i <= m; ++i) {
			dp[1][i] = i == arr[1] ? 0 : -INF;
		}
	}
	for (int i = 2; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (arr[i] != -1 && arr[i] != j) {
				dp[i][j] = -INF;
				continue;
			}
			int ans = 0;
			for (int k = 1; k <= m; ++k) {
				ans = std::max(ans, dp[i - 1][k] + score[k][j]);
			}
			dp[i][j] = ans;
		}
	}
	/*for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			std::cout << dp[i][j] << ' ';
		}
		std::cout << std::endl;
	}*/

	int ans = 0;
	for (int i = 1; i <= m; ++i) {
		ans = std::max(ans, dp[n][i]);
	}
	std::cout << ans << std::endl;
}

int main()
{
	std::ios::sync_with_stdio(false);
	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i) {
		std::cin >> n >> m;
		for (int i = 1; i <= m; ++i) {
			for (int j = 1; j <= m; ++j) {
				std::cin >> score[i][j];
			}
		}
		for (int i = 1; i <= n; ++i)
			std::cin >> arr[i];
		work();
	}
}
