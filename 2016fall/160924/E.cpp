#include<cstdio>
#include<vector>
#include<string>
#include<map>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 200010;
int to[N << 1], nxt[N << 1], head[N], cnt;
void add(int x, int y) {
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
	to[++ cnt] = x; nxt[cnt] = head[y]; head[y] = cnt;
}

int n, m;
string name[N];
map<string,int>mp;
vector<int>have[N];
int fa[N][20], dep[N], col[N], l[N], r[N];


void dfs(int x){
	for(int i = 1; (1 << i) <= dep[x]; i ++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for(int i = head[x]; i; i = nxt[i])
		if (to[i] != fa[x][0]) {
			fa[to[i]][0] = x;
			dep[to[i]] = dep[x] + 1;
			dfs(to[i]);
		}
}

int LCA(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	int t = dep[x] - dep[y];
	for(int i = 0; i <= 18; i ++)
		if ((1 << i) & t) x = fa[x][i];
	for(int i = 18; i >= 0; i --)
		if (fa[x][i] != fa[y][i])
			x = fa[x][i],
			y = fa[y][i];
	if (x == y) return x;
	return fa[x][0];
}

int dist(int x, int y){
	if (!x || !y) return 1e8;
	return dep[x] + dep[y] - dep[LCA(x, y)] * 2;
}

int main(){
	while(scanf("%d%d", &n, &m) != EOF) {
		cnt = 0;
		memset(head, 0, sizeof head);
		memset(col, 0, sizeof col);
		mp.clear();
		int tot = 0;
		memset(fa, 0, sizeof fa);
		memset(dep, 0, sizeof dep);
		memset(l, 0, sizeof l);
		memset(r, 0, sizeof r);
		for(int i = 1; i <= n; i ++) {
			cin >> name[i];
			if (!mp[name[i]]) mp[name[i]] = ++ tot;
			col[i] = mp[name[i]];
			have[col[i]].push_back(i);
		}
		for(int i = 1; i < n; i ++) {
			int x, y;
			cin >> x >> y;
			add(x, y);
		}
		dfs(1);
		for(int i = 1; i <= tot; i ++) {
			for(int j = 0; j < have[i].size(); j ++)
				if (!l[i]) l[i] = have[i][j];
				else if (!r[i]) r[i] = have[i][j];
				else {
					int d1 = dist(l[i], have[i][j]),
						d2 = dist(r[i], have[i][j]),
						d  = dist(l[i], r[i]);
					if (d1 > d && d1 > d2) r[i] = have[i][j];
					if (d2 > d && d2 > d1) l[i] = have[i][j];
				}
		}
		for(int i = 1; i <= tot; i ++) if (!r[i]) r[i] = l[i];
		string s1, s2;
		for(int i = 1; i <= m; i ++) {
			cin >> s1 >> s2;
			int t1 = mp[s1], t2 = mp[s2];
			if (!t1 || !t2) {
				puts("-1");
				continue;
			}
			if (t1 == t2) printf("%d\n", dist(l[t1], r[t1]) + 1);
			else {
				int ans = 0;
				if (l[t1]) {
					if (l[t2]) ans = max(ans, dist(l[t1], l[t2]));
					if (r[t2]) ans = max(ans, dist(l[t1], r[t2]));
				}
				if (r[t1]) {
					if (l[t2]) ans = max(ans, dist(r[t1], l[t2]));
					if (r[t2]) ans = max(ans, dist(r[t1], r[t2]));
				}
				printf("%d\n", ans + 1);
			}
		}
		for(int i = 1; i <= tot; i ++) have[i].clear();
	}
	return 0;
}
