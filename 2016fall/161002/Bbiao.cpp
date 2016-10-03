#include <cstdlib>
#include <cstring>
#include <iostream>

const int N = 10;

int board[N][N];
int cnt[N][N];
bool filled[N][N];
int mem[N][N][N][N];
int place[10][3];

inline bool valid(int x)
{
	return x >= 0 && x < N;
}

void print()
{
	std::cout << '"';
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			std::cout << (board[i][j] ? '#' : '.');
		}
		std::cout << "\\n";
	}
	std::cout << "\",\n";
}

void work()
{
	for (int i = 0; i < 10; ++i) {
		place[i][0] = rand() % (N);
		place[i][1] = rand() % (N);
		place[i][2] = rand() & 1;
	}
	std::memset(board, 0, sizeof(board));
	std::memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < 4; ++i) {
		if (!valid(place[i][0]) || !valid(place[i][1]))
			return;
		if (cnt[place[i][0]][place[i][1]])
			return;
		board[place[i][0]][place[i][1]] = 1;
		for (int x = -1; x <= 1; ++x) {
			for (int y = -1; y <= 1; ++y) {
				if (valid(place[i][0] + x) && valid(place[i][1] + y))
					++cnt[place[i][0] + x][place[i][1] + y];
			}
		}
	}

	for (int i = 4; i < 7; ++i) {
		for (int d = 0; d < 2; ++d) {
			if (!valid(place[i][0]) || !valid(place[i][1] + d))
				return;
			if (cnt[place[i][0]][place[i][1] + d])
				return;
			board[place[i][0]][place[i][1] + d] = 1;
		}
		for (int x = -1; x <= 1; ++x) {
			for (int y = -1; y <= 2; ++y) {
				if (valid(place[i][0] + x) && valid(place[i][1] + y))
					++cnt[place[i][0] + x][place[i][1] + y];
			}
		}

	}
	for (int i = 7; i < 9; ++i) {
		for (int d = 0; d < 3; ++d) {
			if (!valid(place[i][0]) || !valid(place[i][1] + d))
				return;
			if (cnt[place[i][0]][place[i][1] + d])
				return;

			board[place[i][0]][place[i][1] + d] = 1;
		}
		for (int x = -1; x <= 1; ++x) {
			for (int y = -1; y <= 3; ++y) {
				if (valid(place[i][0] + x) && valid(place[i][1] + y))
					++cnt[place[i][0] + x][place[i][1] + y];
			}
		}

	}
	for (int i = 9; i < 10; ++i) {
		for (int d = 0; d < 4; ++d) {
			if (!valid(place[i][0]) || !valid(place[i][1] + d))
				return;
			if (cnt[place[i][0]][place[i][1] + d])
				return;

			board[place[i][0]][place[i][1] + d] = 1;
		}
		for (int x = -1; x <= 1; ++x) {
			for (int y = -1; y <= 4; ++y) {
				if (valid(place[i][0] + x) && valid(place[i][1] + y))
					if (++cnt[place[i][0] + x][place[i][1] + y] > 1)
						return;
			}
		}

	}
	int ans = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (!filled[i][j] && board[i][j]) {
				std::memcpy(mem[i][j], board, sizeof(board));
				filled[i][j] = true;
			}
			if (filled[i][j]) {
				++ans;
			}
			//std::cout << ans << std::endl;
		}
	}
	//std::cout << ans << std::endl;
	if (ans == 100) {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				std::memcpy(board, mem[i][j], sizeof(board));
				print();
			}
		}
		std::exit(0);
	}
}

int main()
{
	srand(time(0));
	for (long long i = 0; i < 10000000000; ++i) {
		work();
	}
}
