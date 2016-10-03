#include <cstdio>

const int N = 120000;

struct Edge {
	int a, b;
} black[N], white[N];

int mb, mw;

struct UFO {
	int pa[N];
	void init(int n) {
		for (int i = 0; i <= n; ++i) {
			pa[i] = i;
		}
	}
	int find(int a) {
		return pa[a] == a ? a : pa[a] = find(pa[a]);
	}
	void merge(int a, int b) {
		pa[find(a)] = find(b);
	}
} uf0, uf1;

int n, m;

int getfibo(int t)
{
	int a = 1, b = 1;
	while (b < t) {
		int t = b;
		b = a + b;
		a = t;
	}
	return b;
}

bool work()
{
	mb = mw = 0;
	scanf("%d%d", &n, &m);
	uf0.init(n);
	uf1.init(n);
	for (int i = 0; i < m; ++i) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		if (c)
			white[mw++] = (Edge){a, b};
		else
			black[mb++] = (Edge){a, b};
	}

	// phase 0
	for (int i = 0; i < mb; ++i)
		uf0.merge(black[i].a, black[i].b);

	// phase 1.0
	int cntw = 0;
	for (int i = 0; i < mw; ++i) {
		if (uf0.find(white[i].a) != uf0.find(white[i].b)) {
			uf0.merge(white[i].a, white[i].b);
			uf1.merge(white[i].a, white[i].b);
			++cntw;
		}
	}

	// phase 1.1
	int common = uf0.find(1);
	for (int i = 2; i <= n; ++i) {
		if (uf0.find(i) != common)
			return false;
	}

	// phase 2
	int tgt = getfibo(cntw);
	for (int i = 0; i < mw && cntw < tgt; ++i) {
		if (uf1.find(white[i].a) != uf1.find(white[i].b)) {
			uf1.merge(white[i].a, white[i].b);
			++cntw;
		}
	}

	return cntw == tgt;
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int T = 1; T <= t; ++T) {
		printf("Case #%d: ", T);
		bool ans = work();
		puts(ans ? "Yes" : "No");
	}
}
