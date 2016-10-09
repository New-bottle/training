#include<cstdio>
#include<cmath>
#include<map>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int N = 1000010;
int n, m, k;

map<int, int> sg;
map<int, bool> vis;

bool getsg(int v) {
	if (vis[v]) return sg[v];
//	printf("getsg %d\n", v);
	vis[v] = 1;
	map<int,bool> mark;
	int lim = sqrt(double(v));
	for(int i = 1; i <= lim; i ++) {
		if (v % i == 0) {
			if (v / i >= k && i != 1) mark[getsg(v / i)] = 1;
			if (i >= k && i != v) mark[getsg(i)] = 1;
		}
	}
	/*
	for(int i = 1; i <= tot; i ++)
		if (v % factor[i] == 0 && v / factor[i] >= k)
			mark[getsg(v / factor[i])] = 1;
			*/
	for(int i = 0; i <= 100000; i ++)
		if (mark[i] == 0) {
//			printf("sg[%d] = %d\n", v, i);
			return (sg[v] = i);
		}
//	return (sg[v] = 0);
}

int main(){
	scanf("%d%d%d", &n, &m, &k);
	if ((n & 1) == 0) {
		puts("Marsel");
		return 0;
	}
	if ((m & 1) == 0) {
		if (m / 2 >= k) puts("Timur");
		else puts("Marsel");
		return 0;
	}
	if (getsg(m)) puts("Timur");
	else puts("Marsel");
	return 0;
}
