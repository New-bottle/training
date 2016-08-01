#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int N = 100010;
int fa[N], n, m, P, size[N], rank[N];
int getfa(int x){return fa[x] == x ? x : fa[x] = getfa(fa[x]);}

LL Pow(LL a, int b){
	if (b < 0) return 1;
	LL r = 1;
	while(b){
		if (b & 1) r = (LL) r * a % P;
		a = (LL) a * a % P;
		b >>= 1;
	}
	return r;
}

int main(){
	scanf("%d%d%d", &n, &m, &P);
	for(int i = 1; i <= n; i ++) fa[i] = i, size[i] = 1;
	int x, y;
	int num = 0;
	bool sign = 0;
	for(int i = 1; i <= m; i ++){
		scanf("%d%d", &x, &y);
		int fx = getfa(x), fy = getfa(y);
		if (fx == fy) {
			sign = 1;
			continue;
		}
		fa[fx] = fy;
		size[fy] += size[fx];
		num ++;
	}
	int ans = Pow(n, n - num - 2);
	for(int i = 1; i <= n; i ++) if (fa[i] == i) ans = (LL)ans * size[i] % P;
	if (num == n - 1) ans = 1;
	printf("%d\n", ans % P);
	return 0;
}
