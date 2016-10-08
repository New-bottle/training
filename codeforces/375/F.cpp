#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 200010, M = 400010;

struct edge {
	int x, y;
}e[M];

int n, m, s, t, ds, dt, fa[N];
int getfa(int x){return fa[x] == x ? x : fa[x] = getfa(fa[x]);}
bool used[M];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i ++)
		scanf("%d%d", &e[i].x, &e[i].y);
	scanf("%d%d%d%d", &s, &t, &ds, &dt);
	for(int i = 1; i <= n; i ++) fa[i] = i;
	int num = 0;
	for(int i = 1; i <= m; i ++) {
		int x = e[i].x, y = e[i].y;
		if (x == s || x == t || y == s || y == t) continue;
		int f1 = getfa(x), f2 = getfa(y);
		if (f1 != f2) {
			fa[f1] = f2;
			num ++;
			used[i] = 1;
		}
	}
	int d1 = 0, d2 = 0;
	for(int i = 1; i <= m; i ++) {
		if (used[i]) continue;
		int x = e[i].x, y = e[i].y;
		if (y == s) swap(x, y);
		if (x == s) {
			int f1 = getfa(x), f2 = getfa(y);
			if (f1 != f2) {
				fa[f1] = f2;
				if (y == t) d2 ++;
				d1 ++;
				used[i] = 1;
			}
		}
	}
	for(int i = 1; i <= m; i ++) {
		if (used[i]) continue;
		int x = e[i].x, y = e[i].y;
		if (y == t) swap(x, y);
		if (x == t) {
			int f1 = getfa(x), f2 = getfa(y);
			if (f1 != f2) {
				fa[f1] = f2;
				d2 ++;
				used[i] = 1;
			}
		}
	}
	if (d1 <= ds && d2 <= dt) {
		puts("Yes");
		for(int i = 1; i <= m; i ++) printf("%d %d\n", e[i].x, e[i].y);
	} else puts("No");
	return 0;
}
