#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<deque>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 110;

int mp[N][N], n, m, belong[N];
bool used[N * N];

deque<int>have[3];

void add(int x, int y, int v) {
//	printf("add %d %d %d %d\n", x, y, v, have[v].front());
	mp[x][y] = have[v].front();
	mp[y][x] = -1;
	have[v].pop_front();
}

void solve() {
	memset(mp, 0, sizeof mp);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i ++) have[i % 3].push_back(i);

	int ed[3];
	for(int i = n - 3; i <= n; i ++)
		ed[i % 3] = i;

	for(int i = 1; i < n; i ++)
		add(i, i + 1, i % 3);
	for(int i = 0; i < 3; i ++)
		add(ed[i], i + 1, i);

	for(int l = 0; l < 3; l ++) {
		while(have[l].size()) {
			for(int i = (l + 2) % 3 + 1; i <= n; i += 3)
				for(int j = l + 1; j <= n; j += 3) if (i != j)
					if (!mp[i][j] && have[l].size()) add(i, j, l);
		}
	}
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++) if (mp[i][j] > 0) printf("%d %d %d\n", i, j, mp[i][j]);
}

int main(){
	int T;
	scanf("%d", &T);
	for(int cs = 1; cs <= T; cs ++) {
		printf("Case #%d:\n", cs);
		solve();
	}
	return 0;
}
