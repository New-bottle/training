//#pragma GCC optimize("Ofast")
#include <bitset>
#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <vector>

const int N = 512;
int n;
int len;

char buf[32768];
std::map<std::string, int> mp;
std::string ss[N];
std::bitset<26> occ[N];
bool vis[N];
int nss;

struct Rule {
	int l, r;
} rule[N];

std::string leaf[N];
bool isleaf[N];

void efs(int node)
{
	if (vis[node])
		return;
	vis[node] = true;
	if (isleaf[node]) {
		for (unsigned i = 0; i < leaf[node].size(); ++i) {
			unsigned char ch = leaf[node][i];
			occ[node][ch - 'a'] = 1;
		}
	} else {
		efs(rule[node].l);
		efs(rule[node].r);
		occ[node] = occ[rule[node].l] | occ[rule[node].r];
	}
}

int getstr(const std::string& s)
{
	if (!mp.count(s)) {
		mp.insert(std::make_pair(s, nss));
		occ[nss] = 0;
		return nss++;
	} else {
		return mp[s];
	}
}

int dfs(int node, int p)
{
	if (p == len)
		return p;
	if (occ[node][buf[p] - 'a'] == 0)
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
	nss = 1;
	mp.clear();
	std::memset(vis, 0, sizeof(vis));
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
			scanf("%s", buf); // +
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
	efs(root);
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
