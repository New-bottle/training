#include <cstdio>
#include <cstring>
#include <queue>

int n, m;

int vis[66666];

int bfs()
{
	std::memset(vis, 0, sizeof(vis));
	std::queue<int> q;
	int g = 0;
	for (int i = 0; i < n; ++i) {
		int b;
		scanf("%d", &b);
		g = (g << 1) | b;
	}
	int t1 = 0;
	int t2 = 0;
	int b = 0;
	for (int i = 0; i < m; ++i) {
		int c;
		scanf("%d", &c);
		for (int j = 0; j < c; ++j) {
			t1 = (t1 << 1) | b;
			t2 = (t2 << 1) | (b ^ 1);
		}
		b ^= 1;
	}
	if (n == 1)
		return 0;
	q.push(t1);
	q.push(t2);
	vis[t1] = 1;
	vis[t2] = 1;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		if (v == g)
			return vis[g] - 1;
		for (int i = 0; i < n - 1; ++i) {
			int nv = v;
			int blo = (v >> i) & 1;
			int bhi = (v >> (i + 1)) & 1;
			nv = nv & ~(1 << i);
			nv = nv & ~(1 << (i + 1));
			if (bhi)
				nv = nv | (1 << i);
			if (blo)
				nv = nv | (1 << (i + 1));
			if (vis[nv])
				continue;
			vis[nv] = vis[v] + 1;
			q.push(nv);
		}
	}
	return -1;
}

void work()
{
	int ans = bfs();
	printf("%d\n", ans);
}

int main()
{
	while (2 == scanf("%d%d", &n, &m)) {
		work();
	}
	return 0;
}
