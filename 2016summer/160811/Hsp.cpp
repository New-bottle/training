#include <bitset>
#include <iostream>
#include <vector>
#include <unordered_set>

const int Mdepth = 6;

int biao[256];

std::bitset<1000> bs;

struct H {
	std::size_t operator () (const std::pair<int, int>& p) const {
		return p.first * 33 + p.second;
	}
};

std::pair<int, int> ops[100];
int opn;

std::unordered_set<std::pair<int, int> , H> set;

bool ok(int a)
{
	for (int i = 0; i < 8; ++i) {
		bs[0] = 0;
		bs[1] = 1;
		bs[2] = i & 1;
		bs[3] = i & 2;
		bs[4] = i & 4;
		int p = 5;
		for (int i = 0; i < opn; ++i) {
			auto& op = ops[i];
			bs[p++] = !(bs[op.first] && bs[op.second]);
		}
		if (bs[p - 1] != (a >> i & 1))
			return false;
	}
	return true;
}

void test()
{
	int i = 253;
	//for (int i = 0; i < 256; ++i) {
		if (biao[i] > opn && ok(i))
			biao[i] = opn;
	//}
}

void dfs(int depth)
{
	if (depth == Mdepth)
		return;
	for (int i = 0; i < depth + 5; ++i) {
		for (int j = i; j < depth + 5; ++j) {
			if (set.count(std::make_pair(i, j)))
				continue;
			ops[opn++] = {i, j};
			set.emplace(i, j);
			test();
			dfs(depth + 1);
			--opn;
			set.erase(std::make_pair(i, j));
		}
	}
}

int main()
{
	 for (int i = 0; i < 256; ++i) {
		 biao[i] = 1000000;
	 }
	 dfs(0);
	 for (int i = 0; i < 256; ++i) {
		 std::cout << i << ' ' << biao[i] << std::endl;
	 }

	 return 0;
}
