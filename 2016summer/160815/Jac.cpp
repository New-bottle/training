#include <iostream>
#include <map>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <list>
#include <vector>

using namespace std;
const int mod = 10007;
list<pair<int, int> > number[40][10007];
int big[33];
int total = 0;
int total0;
int getans(int p, int q) {
	/*int now = 0;
	int kk = target % mod;
	
	for (list<pair<int, int> > :: iterator it = number[rest][kk].begin(); it != number[rest][kk].end(); it++) {
		if (it->first == target) {
			return it->second;
		}
	}
	int result = 0;
	int step;
	for (step = 1; ; step++) {
		now += (1 << step - 1);
		if (now > (target - 1) / 2) {
			break;
		}
	}
	step = lower_bound(big + 1, big + 31, (target - 1)/ 2) - big;
	now = (1 << step) - 1;
	if (now <= (target - 1) / 2) {
		now = now * 2 + 1;
		step++;
	}

	if (now == target) {
		number[rest][kk].push_back(make_pair(target, result = step));
		return result;
	}
	
	int need = now * 2 + 1 - target;
	result = min(max(need - rest, 0) + step + 1, step + 1 + getans(rest + 1, target - now));
	number[rest][kk].push_back(make_pair(target, result));
	return result;*/
	int rest = 0;
	int step = 0;
	int answer = 111111;
	for (; ;) {
		int i;
		for (i = 1; ; i++) {
			step++;
			p -= (1 << i - 1);
			if (p <= q) {
				break;
			}
		}
		if (q - max(p, 0) <= rest) {
			answer = min(answer, step + rest);
			break;
		}
		answer = min(answer, step + (q - max(p, 0)));
		rest++;
		p += (1 << i - 1);
		step--;
	}
	
	return answer;
}
void solve() {
	int p, q;
	scanf("%d%d", &p, &q);
	if (p <= q) {
		printf("%d\n", q - p);
	} else {
		printf("%d\n", getans(p, q));
	}
}
int main() {
	freopen("J.in","r",stdin);
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= 30; i++) {
		big[i] = 1 << i;
	}
	for (int i = 1; i <= tests; i++) {
		solve();
	}
	//cout << total << " " << total0 << endl;
	return 0;
}
