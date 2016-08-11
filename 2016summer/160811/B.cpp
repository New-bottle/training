#pragma GCC optimize("O2")
#include <algorithm>
#include <cstdio>
#include <map>
#include <deque>

#define LL "%I64d"

std::map<int, long long> mp;
std::deque<int> q;
int top;
int n, k;

char buf[256];

void bye(int p)
{
	printf("Bye %d: " LL "\n", p, mp[p]);
}

void work()
{
	scanf("%d", &n);
	top = 0;
	mp.clear();
	q.clear();
	for (int i = 1; i <= n; ++i) {
		k = i;
		printf("Operation #%d: ", i);
		scanf("%s", buf);
		int x;
		if (buf[1] == 'd') { // Add
			scanf("%d", &x);
			if (mp.count(x)) {
				puts("same priority.");
				continue;
			}
			q.push_back(x);
			mp[x] = 0;
			puts("success.");
		} else if (buf[0] == 'C' && buf[1] == 'l') { // Close
			scanf("%d", &x);
			auto it = mp.find(x);
			if (it == mp.end()) {
				puts("invalid priority.");
				continue;
			}
			long long c = it->second;
			mp.erase(it);
			if (top == x)
				top = 0;
			auto jt = std::find(q.begin(), q.end(), x);
			q.erase(jt);
			printf("close %d with " LL ".\n", x, c);
		} else if (buf[0] == 'C' && buf[2] == 'a') { // Chat
			scanf("%d", &x);
			if (top) {
				mp[top] += x;
			} else if (q.empty()) {
				puts("empty.");
				continue;
			} else {
				mp[q.front()] += x;
			}
			puts("success.");
		} else if (buf[0] == 'R') { // Rotate
			scanf("%d", &x);
			if (x < 1 || x > q.size()) {
				puts("out of range.");
				continue;
			}
			int tmp = q[x - 1];
			for (int i = x - 1; i > 0; --i)
				q[i] = q[i - 1];
			q[0] = tmp;
			puts("success.");
		} else if (buf[0] == 'P') { // Prior
			// XXX
			if (q.empty()) {
				puts("empty.");
				continue;
			}
			auto p = mp.rbegin()->first;
			auto it = std::find(q.begin(), q.end(), p);
			for (; it != q.begin(); --it)
				*it = *(it - 1);
			q[0] = p;
			puts("success.");
		} else if (buf[0] == 'C' && buf[1] == 'h') { // Choose
			scanf("%d", &x);
			//if (x == top) {
				// XXX
			//	puts("success.");
			//	continue;
			//}
			auto jt = mp.find(x);
			if (jt == mp.end()) {
				puts("invalid priority.");
				continue;
			}
			auto it = std::find(q.begin(), q.end(), x);
			for (; it != q.begin(); --it)
				*it = *(it - 1);
			q[0] = x;
			puts("success.");
		} else if (buf[0] == 'T') { // Top
			scanf("%d", &x);
			if (x == top) {
				puts("success.");
				continue;
			}
			auto it = mp.find(x);
			if (it == mp.end()) {
				puts("invalid priority.");
				continue;
			}
			//auto jt = std::find(q.begin(), q.end(), x);
			//q.erase(jt);
			top = x;
			puts("success.");
		} else if (buf[0] == 'U') { // Untop
			if (!top) {
				puts("no such person.");
				continue;
			} else {
				//q.push_front(top);
				top = 0;
			}
			puts("success.");
		}
	}
	if (top && mp[top])
		bye(top);
	for (auto& p : q) {
		if (p == top)
			continue;
		if (mp[p])
			bye(p);
	}
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t --> 0) {
		work();
	}
}
