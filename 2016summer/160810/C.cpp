#include <algorithm>
#include <cstdio>

const int N = 1100;
const int M = 11000;

int n, m;

int pa[N];

int getpa(int a)
{
	return pa[a] == a ? a : pa[a] = getpa(pa[a]);
}

void merge(int a, int b)
{
	pa[getpa(pa[a])] = getpa(b);
}

struct Edge {
	int x, y, w;
	bool operator < (const Edge& r) const {
		return w < r.w;
	}
} ed[M];

void work()
{
	for (int i = 1; i <= n; ++i)
		pa[i] = i;
	for (int i = 0; i < m; ++i)
		scanf("%d%d%d", &ed[i].x, &ed[i].y, &ed[i].w);
	std::sort(ed, ed + m);
	int fini = 0;
	int ans = 0;
	for (int i = 0; i < m; ++i) {
		if (getpa(ed[i].x) != getpa(ed[i].y)) {
			merge(ed[i].x, ed[i].y);
			++fini;
			if (fini * 2 == n) {
				ans = ed[i].w;
				break;
			}
		}
	}
	printf("%d\n", ans);
}

int main()
{
	while (~scanf("%d%d", &n, &m) && n)
		work();
	return 0;
}
