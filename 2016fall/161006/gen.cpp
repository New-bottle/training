#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;

int main(){
	srand(time(0));
	freopen("I.in","w",stdout);
	int n = 10000000, m = 100000, q = 100000;
	printf("%d %d %d\n", n, m, q);
	for(int i = 1; i <= m; i ++) {
		int l = rand() % n + 1, r = rand() % n + 1;
		if (l > r) swap(l, r);
		printf("%d %d %d\n", l, r, rand() % 1000 + 1);
	}
	for(int i = 1; i <= q; i ++) {
		int l = rand() % n + 1, r = rand() % n + 1;
		if (l > r) swap(l, r);
		printf("%d %d %d\n", l, r, rand() % 1000 + 1);
	}
	return 0;
}
