#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#define N 510
#define M 3010
using namespace std;
int n, m;
int f[N];
int getf(int x){
	return f[x] == x ? x : f[x] = getf(f[x]);
}
int main(){
	int cnt = 0;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++) f[i] = i;
	for(int i = 1; i <= m; i ++){
		int x, y;
		scanf("%d%d", &x, &y);
		int fx = getf(x);
		int fy = getf(y);
		if(fx != fy){
			cnt ++;
			f[fx] = fy;
		}
	}
	
	printf("%d\n", m - cnt);
	return 0;
}
