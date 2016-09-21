#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
	int n, m;
	std::ios::sync_with_stdio(false);
	while (std::cin >> n >> m) {
		std::vector<std::pair<int, int> > v;
		for (int i = 0; i < m; ++i) {
			int b, a;
			std::cin >> b >> a;
			v.push_back(std::make_pair(b, a));
		}
		std::sort(v.begin(), v.end());
		int ans = n + 1;
		int cb, ce;
		if (m == 0)
			goto finish;
		cb = v[0].first;
		ce = v[0].second;
		for (int i = 1; i < m; ++i) {
			if (v[i].first > ce) {
				ans += 2 * (ce - cb);
				cb = v[i].first;
				ce = v[i].second;
			} else {
				ce = std::max(ce, v[i].second);
			}
		}
		ans += 2 * (ce - cb);
finish:
		std::cout << ans << std::endl;
	}
}
