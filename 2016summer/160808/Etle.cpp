#pragma GCC optimize("Ofast")
#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <vector>

const int N = 512;
int n;
int len;

char buf[32];
std::map<std::string, int> mp;
std::string ss[N];
int nss;

struct Rule {
	int l, r;
} rule[N];

std::string leaf[N];
bool isleaf[N];

int getstr(const std::string& s)
{
	if (!mp.count(s)) {
		mp.insert(std::make_pair(s, nss));
		return nss++;
	} else {
		return mp[s];
	}
}

int dfs(int node, int p)
{
	if (p == len)
		return p;
	if (isleaf[node]) {
		int l = leaf[node].size();
		for (int i = 0; i < l && p < len; ++i) {
			if (leaf[node][i] == buf[p])
				++p;
		}
	} else {
		p = dfs(rule[node].l, p);
		p = dfs(rule[node].r, p);
	}
	return p;
}

void work()
{
	nss = 0;
	mp.clear();
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%s", buf); // lhs of =
		std::string s(buf);
		int p = getstr(s);

		scanf("%s", buf); // =
		scanf("%s", buf); // lhs of +
		s = std::string(buf);
		if (std::isupper(s[0])) {
			isleaf[p] = false;
			int lhs = getstr(s);
			scanf("%s", buf); // =
			scanf("%s", buf); // rhs of +
			int rhs = getstr(std::string(buf));
			rule[p].l = lhs;
			rule[p].r = rhs;
		} else {
			isleaf[p] = true;
			leaf[p] = s;
		}
	}
	scanf("%s", buf);
	int root = getstr(std::string(buf));
	scanf("%s", buf); // pattern
	len = std::strlen(buf);
	int ans = dfs(root, 0);
	if (ans == len) {
		puts("YES");
	} else {
		puts("NO");
	}
}


int main()
{
	int t;
	scanf("%d", &t);
	while (t --> 0) {
		work();
	}
	return 0;
}
