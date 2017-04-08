#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 3000010;

int ch[N][2], cnt, n, m, who[N], a[N];

void add(int val, int id)
{
	int x = 1, y;
	for (int i = 30; i >= 0; --i) {
		y = val >> i & 1;
		if (!ch[x][y]) ch[x][y] = ++cnt;
		x = ch[x][y];
	}
	if (!who[x]) who[x] = id;
}

int query(int val)
{
	int x = 1, y;
	for (int i = 30; i >= 0; --i) {
		y = val >> i & 1;
		if (ch[x][y ^ 1]) x = ch[x][y ^ 1];
		else x = ch[x][y];
	}
	return who[x];
}
int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= cnt; ++i) ch[i][0] = ch[i][1] = who[i] = 0;
		cnt = 1;
		int x;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &x);
			add(x, i);
		}
		for (int i = 1; i <= m; ++i) {
			scanf("%d", &x);
			printf("%d\n", query(x));
		}
		puts("");
	}
	return 0;
}
