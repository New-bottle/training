#include <bitset>
#include <iostream>
#include <vector>
#include <unordered_set>

const int Mdepth = 4;

int biao[256];

std::bitset<1000> bs;

struct H {
	std::size_t operator () (const std::pair<int, int>& p) const {
		return p.first * 33 + p.second;
	}
};
std::vector<std::pair<int, int> > ops;
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
		for (auto op : ops) {
			bs[p++] = !(bs[op.first] && bs[op.second]);
		}
		if (bs[p - 1] != (a >> i & 1))
			return false;
	}
	return true;
}

void test()
{
	for (int i = 0; i < 256; ++i) {
		if (biao[i] > ops.size() && ok(i))
			biao[i] = ops.size();
	}
}

void dfs(int depth)
{
	if (depth == Mdepth)
		return;
	for (int i = 0; i < depth + 5; ++i) {
		for (int j = i; j < depth + 5; ++j) {
			if (set.count(std::make_pair(i, j)))
				continue;
			ops.emplace_back(i, j);
			set.emplace(i, j);
			test();
			dfs(depth + 1);
			ops.pop_back();
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
