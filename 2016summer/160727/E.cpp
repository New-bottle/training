#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 20010;
int n, m, fa[N], g[N], rt, val, num;
int getfa(int x){
	return fa[x] == x ? x : (getfa(fa[x]), g[x] ^= g[fa[x]], fa[x] = fa[fa[x]]);
}

bool sign = 0;
void change(int p, int q, int v){
	if (v == -1){
		if (rt == -1){
			rt = getfa(p);
			val = g[p] ^ q;
		}else{
			if (getfa(p) == rt){
				if ((g[p] ^ q) != val){
					sign = 0;
					printf("The first %d facts are conflicting.\n", num);
					return;
				}
			}else{
				g[fa[p]] = g[p] ^ q ^ val;
				fa[fa[p]] = rt;
			}
		}
	}else{
		int fx = getfa(p), fy = getfa(q);
		if (fx == fy){
			if (v != (g[p] ^ g[q])){
				sign = 0;
				printf("The first %d facts are conflicting.\n", num);
				return;
			}
		}else{
			if (fx == rt) swap(fx, fy);
			fa[fx] = fy;
			g[fx] = g[p] ^ g[q] ^ v;
		}
	}
}

int k[25];
void query(int len){
	int ans = 0, cnt = 0, pos = 0;
	for(int i = 1; i <= len; i ++){
		getfa(k[i]);
		ans = ans ^ g[k[i]];
		k[i] = fa[k[i]];
	}
	sort(k + 1, k + len + 1);
	bool yes = 1;
	while(pos < len){
		pos ++; cnt = 1;
		while(pos < len && k[pos + 1] == k[pos]) cnt ++, pos ++;
		if (cnt & 1){
			if (k[pos] == rt) ans ^= val;
			else{
				yes = 0;
				break;
			}
		}
	}
	if (yes) printf("%d\n", ans);
	else puts("I don't know.");
}

char s[20];
int main(){
	int cs = 0;
	while(scanf("%d%d", &n, &m) == 2 && n + m){
		printf("Case %d:\n", ++ cs);
		rt = val = -1;
		num = 0;
		sign = 1;
		for(int i = 0; i < n; i ++) g[i] = 0, fa[i] = i;
		int p, q, v;
		for(int i = 1; i <= m; i ++){
			scanf("%s", s);
			if (s[0] == 'I'){
				num ++;
				gets(s); v = -1;
				sscanf(s, "%d%d%d", &p, &q, &v);
				if (sign) change(p, q, v);
			}else{
				scanf("%d", &p);
				k[p + 1] = -1;
				for(int j = 1; j <= p; j ++) scanf("%d", &k[j]);
				if (sign) query(p);
			}
		}
		puts("");
	}
	return 0;
}
