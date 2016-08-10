#include <cstdio>
#include <cstring>

char buf[2][512];
int n;

bool topo[26][26];
bool onst[26];
bool fini[26];

bool process(int a, int b)
{
	//puts(buf[a]);
	//puts(buf[b]);
	for (int i = 0; ; ++i) {
		if (!buf[a][i] || !buf[b][i]) {
			if (!buf[a][i] && !buf[b][i])
				return true;
			if (!buf[a][i])
				return true;
			return false;
		}
		int c = buf[a][i] - 'a';
		int d = buf[b][i] - 'a';
		if (c != d) {
			//printf("adde %c %c\n", buf[a][i], buf[b][i]);
			topo[c][d] = true;
			return true;
		}
	}
}

bool toposort(int node)
{
	if (fini[node])
		return true;
	if (onst[node]) {
		//printf("WA %d\n", node);
		return false;
	}
	onst[node] = true;
	bool ans = true;
	for (int i = 0; i < 26; ++i) {
		if (topo[node][i])
			ans = ans && toposort(i);
	}
	onst[node] = false;
	fini[node] = true;
	return ans;
}

void work()
{
	std::memset(topo, 0, sizeof(topo));
	std::memset(onst, 0, sizeof(onst));
	std::memset(fini, 0, sizeof(fini));
	bool ans = true;
	for (int i = 0; i < n; ++i) {
		scanf("%s", buf[i & 1]);
		if (i > 0)
			ans = ans && process((i & 1) ^ 1, i & 1);
	}
	for (int i = 0; i < 26; ++i)
		ans = ans && toposort(i);
	puts(ans ? "yes" : "no");
}

int main()
{
	while (~scanf("%d", &n) && n)
		work();
	return 0;
}
