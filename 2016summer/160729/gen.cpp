#include<cstdio>
#include<ctime>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;
int fa[N];
int getfa(int x){return fa[x] == x ? x : fa[x] = getfa(fa[x]);}
void make(){
	int n = 5, m = 5;
	printf("%d %d\n", n, m);
	for(int i = 1; i <= n; i ++) fa[i] = i;
	for(int i = 1; i < n; i ++){
		int x = rand() % n + 1, y = rand() % n + 1, fx = getfa(x), fy = getfa(y);
		if (fx == fy){
			i --;
			continue;
		}
		fa[fx] = fy;
		printf("%d %d\n", x, y);
	}
	for(int i = 1; i <= m; i ++){
		int x = rand() % n + 1, y = rand() % n + 1, v = rand() % 30 - 10;
		printf("%d %d %d\n", x, y, v);
	}
}
int main(){
	srand(time(0));
	int T = 1;
	printf("%d\n", T);
	while(T --){
		make();
	}
	return 0;
}
