#include<cstdio>
#include<map>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
//#define debug

typedef long long LL;
const int N = 200010;
int to[N << 1], nxt[N << 1], head[N], cnt = 0;
LL len[N << 1];
void add(int x, int y, LL z){
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt; len[cnt] = z;
	to[++ cnt] = x; nxt[cnt] = head[y]; head[y] = cnt; len[cnt] = z;
}
int t[N << 1], nt[N << 1], hd[N], cnt2;
LL l[N << 1];
void ins(int x, int y, LL z){
	t[++ cnt2] = y; nt[cnt2] = hd[x]; hd[x] = cnt2; l[cnt2] = z;
//	t[++ cnt2] = x; nt[cnt2] = hd[y]; hd[y] = cnt2; l[cnt2] = z;
}
int n, m, du[N], lim, q, col[N];
LL sum00, sum01, sum11, sum, val[N][2];
int big[N], bigcnt, id[N];
char opt[100];

inline void Change(int x){
	if (du[x] < lim){
		for(int i = head[x]; i; i = nxt[i]){
			if (col[to[i]] ^ col[x]){
				if (col[x]) sum00 += len[i];
				else sum11 += len[i];
				sum01 -= len[i];
			}else{
				if (col[x]) sum11 -= len[i];
				else sum00 -= len[i];
				sum01 += len[i];
			}
			if (du[to[i]] >= lim){
				val[id[to[i]]][col[x]] -= len[i];
				val[id[to[i]]][col[x] ^ 1] += len[i];
			}
		}
	}else{
//		for(;0;);//every edge connected to big point
		for(int i = hd[x]; i; i = nt[i]){
			val[id[t[i]]][col[x]] -= l[i];
			val[id[t[i]]][col[x] ^ 1] += l[i];
		}
		if (col[x] == 0) {
			sum00 -= val[id[x]][0];
			sum11 += val[id[x]][1];
			sum01 = sum01 - val[id[x]][1] + val[id[x]][0];
		}else{
			sum11 -= val[id[x]][1];
			sum00 += val[id[x]][0];
			sum01 = sum01 - val[id[x]][0] + val[id[x]][1];
		}
	}
	col[x] ^= 1;
}

map<int,int>mp[N];
int main(){
	freopen("D.out","w",stdout);
	int cs = 0;
	while(scanf("%d%d", &n, &m) != EOF){
		printf("Case %d:\n", ++ cs);
		lim = sqrt(n) + 1;
		for(int i = 1; i <= n; i ++) scanf("%d", &col[i]);
		int x, y, z;
		for(int i = 1; i <= m; i ++){
			scanf("%d%d%d", &x, &y, &z);
			if (mp[x][y]){
				len[mp[x][y]] += z;
				len[mp[y][x]] += z;
			}else{
				add(x, y, z); du[x] ++; du[y] ++;
				mp[x][y] = cnt - 1;
				mp[y][x] = cnt;
			}
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
		bigcnt = 0;
		for(int x = 1; x <= n; x ++) if (du[x] >= lim){
			big[++ bigcnt] = x;
			id[x] = bigcnt;
			for(int i = head[x]; i; i = nxt[i]){
				val[bigcnt][col[to[i]]] += len[i];
				if (du[to[i]] >= lim) ins(x, to[i], len[i]);
			}
		}

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
		for(int i = 1; i <= n; i ++) head[i] = 0; cnt = 0;
		for(int i = 1; i <= n; i ++) hd[i] = 0; cnt2 = 0;
		for(int i = 1; i <= n; i ++) du[i] = 0;
		for(int i = 1; i <= n; i ++) id[i] = 0;
		for(int i = 1; i <= n; i ++) mp[i].clear();
		sum00 = sum01 = sum11 = sum = 0;
		for(int i = 1; i <= bigcnt; i ++) val[i][0] = val[i][1] = 0;
		for(int i = 1; i <= bigcnt; i ++) big[i] = 0;
		bigcnt = 0;
	}
	return 0;
}
