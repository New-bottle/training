#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;
int to[N << 1], nxt[N << 1], head[N], cnt, len[N << 1];
void add(int x, int y, int z){
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt; len[cnt] = z;
	to[++ cnt] = x; nxt[cnt] = head[y]; head[y] = cnt; len[cnt] = z;
}
int n, m, du[N], lim, num[N];
LL sum00, sum01, sum11, sum;

void Change(int x){
	if (du[x] < lim){
		for(int i = head[x]; i; i = nxt[i])
			if (col[to[i]] ^ col[x]){
				sum01 -= len[i];
				if (col[x]) sum00 += len[i];
				else sum11 += len[i];
			}else{
				if (col[x]) sum11 -= len[i];
				else sum00 -= len[i];
				sum01 += len[i];
			}
	}
	for(int 
}


int main(){
	while(scanf("%d%d", &n, &m) == 2){
		lim = sqrt(n);
		memset(head, 0, sizeof head); cnt = 0;
		memset(du, 0, sizeof du);
		sum00 = sum01 = sum11 = sum = 0;
		for(int i = 1; i <= n; i ++) scanf("%d", &col[i]);
		int x, y, z;
		for(int i = 1; i <= m; i ++){
			scanf("%d%d%d", &x, &y, &z);
			add(x, y, z); du[x] ++; du[y] ++;
			sum += z;
			if (col[x] == 0){
				if (col[y] == 0) sum00 += z;
				else sum01 += z;
			}else{
				if (col[y] == 1) sum11 += z;
				else sum01 += z;
			}
		}
		//get du > lim
		for(int 
		scanf("%d", &q);
		for(int i = 1; i <= q; i ++){
			scanf("%s", opt);
			if (opt[0] == 'A'){
				scanf("%d%d", &x, &y);
				if (x^y) printf("%lld\n", sum01);
				else if (x) printf("%lld\n", sum11);
				else printf("%lld\n", sum00);
			}else{
				scanf("%d", &x);
				Change(x);
			}
		}
	}
	return 0;
}
