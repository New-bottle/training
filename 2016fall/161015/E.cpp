#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 400010;
int to[N << 1], nxt[N << 1], head[N], cnt;
void add(int x, int y) {
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
	to[++ cnt] = x; nxt[cnt] = head[y]; head[y] = cnt;
}

int n, yes[N], size[N], len[N], fa[N], f[N], root;

void dfs(int x) {
	size[x] = 1; f[x] = 0;
	for(int i = head[x]; i; i = nxt[i])
		if (to[i] != fa[x]) {
			fa[to[i]] = x;
			dfs(to[i]);
			size[x] += size[to[i]];
			f[x] = max(f[x], size[to[i]]);
		}
	f[x] = max(f[x], n - size[x]);
	if (f[x] < f[root]) root = x;
}

void findans(int x) {
	size[x] = 1;
	for(int i = head[x]; i; i = nxt[i])
		if (to[i] != fa[x]) {
			fa[to[i]] = x;
			findans(to[i]);
			size[x] += size[to[i]];
		}
}

int belong[N];
void setbelong(int x, int f) {
	belong[x] = f;
	for(int i = head[x]; i; i = nxt[i])
		if (to[i] != fa[x])
			setbelong(to[i], f);
}

int main(){
	f[0] = 1e9;
	scanf("%d", &n);
	for(int i = 1; i < n; i ++) {
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	dfs(1);
	for(int i = 1; i <= n; i ++) fa[i] = 0;
	findans(root);
	int mx0 = 0, mx1 = 0;
	for(int i = head[root]; i; i = nxt[i]) {
		if (size[to[i]] > size[mx0]) mx1 = mx0, mx0 = to[i];
		else if (size[to[i]] > size[mx1]) mx1 = to[i];
	}
	for(int i = head[root]; i; i = nxt[i])
		setbelong(to[i], to[i]);
	yes[root] = 1;

	for(int i = 1; i <= n; i ++) if (i != root) {
		if (n - size[i] - (belong[i] != mx0 ? size[mx0] : size[mx1]) <= n / 2)
			yes[i] = 1;
		if (i != mx0 && belong[i] == mx0 && n - size[i] - (n - size[mx0]) <= n / 2 && n - size[mx0] <= n / 2)
			yes[i] = 1;
		}
	for(int i = 1; i <= n; i ++) printf("%d%c", yes[i], i == n ? '\n' : ' ');
	return 0;
}
