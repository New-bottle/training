#include<cstdio>
#include<ctime>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 10010;
const int Lim = 10;

void gen() {
	int n = 100, m = 3000, q = 1000;
	printf("%d %d\n", n, m);
	for(int i = 2; i <= n; i ++)
		printf("%d %d %d\n", i, rand() % (i - 1) + 1, rand() % Lim);
	for(int i = n; i <= m; i ++) {
		int x = rand() % n + 1, y = rand() % n + 1;
		while(x == y) y = rand() % n + 1;
		printf("%d %d %d\n", x, y, rand() % Lim);
	}
	printf("%d\n", q);
	for(int i = 1; i <= q; i ++) {
		int l = rand() % Lim, r = rand() % Lim;
		if (l > r) swap(l, r);
		printf("%d %d\n", l, r);
	}
}
int main(){
	srand(time(0));
	int T = 1;
	printf("%d\n", T);
	while(T --) {
		gen();
	}
	return 0;
}
