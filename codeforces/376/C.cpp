#include<cstdio>
#include<map>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 200010;

map<int,int>mp[N];
int n, m, c[N], k, l[N], r[N];
int fa[N], size[N];
int getfa(int x) {return fa[x] == x ? x : fa[x] = getfa(fa[x]);}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &c[i]);
	for(int i = 1; i <= n; i ++) fa[i] = i, size[i] = 1;
	for(int i = 1; i <= m; i ++) {
		scanf("%d%d", &l[i], &r[i]);
		int f1 = getfa(l[i]), f2 = getfa(r[i]);
		if (f1 != f2) {
			fa[f1] = f2;
			size[f2] += size[f1];
		}
	}
	for(int i = 1; i <= n; i ++) {
		mp[getfa(i)][c[i]] ++;
	}
	int ans = 0;
	for(int i = 1; i <= n; i ++) if (getfa(i) == i){
		int tmp = 0;
		for(map<int,int> :: iterator it = mp[i].begin(); it != mp[i].end(); ++ it)
			tmp = max(tmp, it -> second);
		ans += size[i] - tmp;
	}
	printf("%d\n", ans);
	return 0;
}
