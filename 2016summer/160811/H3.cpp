#include <bitset>
#include <iostream>
#include <vector>
#include <unordered_set>

const int Mdepth = 7;

int biao[256];

std::bitset<1000> bs;

struct H {
	std::size_t operator () (const std::pair<int, int>& p) const {
		return p.first * 33 + p.second;
	}
};
std::vector<std::pair<int, int> > ops;
std::unordered_set<std::pair<int, int> , H> set;
int hot[100];

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
			if (i > 4) --hot[i - 5];
			if (j > 4) --hot[j - 5];
			++hot[ops.size()];
			ops.emplace_back(i, j);
			set.emplace(i, j);
			bool flag = true;
			for (int i = 0; i < ops.size() - 1; ++i) {
				if (hot[i] > 0) {
					flag = false;
					break;
				}
			}
			if (flag)
				test();

			dfs(depth + 1);
			ops.pop_back();
			if (i > 4) ++hot[i - 5];
			if (j > 4) ++hot[j - 5];
			--hot[ops.size()];
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
