#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1000010;

int du[N], n, m, fa[N], odd[N];
int getfa(int x) {return fa[x] == x ? x : fa[x] = getfa(fa[x]);}

int main(){
	scanf("%d%d", &n, &m);
	int num = 0;
	for(int i = 1; i <= n; i ++) fa[i] = i;
	for(int i = 1; i <= m; i ++) {
		int x, y;
		scanf("%d%d", &x, &y);
//		if (x == y) continue;
		du[x] ++; du[y] ++;
		int f1 = getfa(x), f2 = getfa(y);
		if (f1 != f2) {
			fa[f1] = f2;
			num ++;
		}
	}
	int total = 0;
	for(int i = 1; i <= n; i ++)
		if (du[i] & 1) odd[getfa(i)] ++, total ++;
	total /= 2;
	int ans = 0;
	int oddkuai = 0, evenkuai = 0;
	for(int i = 1; i <= n; i ++) if (odd[i]) oddkuai ++;
	for(int i = 2; i <= n; i ++) if (du[i] == 0) num ++;
	if (n - num > 1) ans = n - num + (total - oddkuai);
	else ans = total;
//	printf("num = %d oddkuai = %d evenkuai = %d total = %d\n", num, oddkuai, evenkuai, total);
	printf("%d\n", ans);
	/*

	total /= 2;
//	total -= oddkuai;
	int ans;
	if (n - num == 1) ans = total;
	else ans = evenkuai + total;
//	if (ans == 1) ans = 0;
	printf("%d\n", ans);
	*/
	return 0;
}
