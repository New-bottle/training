#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 10010;
bool vis[N];
bool check(int x) {
	if (x == 1) return 0;
	for(int i = 2; i < x; i ++)
		if (x % i == 0) return 0;
	int t = x, nxt = 0;
	memset(vis, 0, sizeof vis);
	do{
		if (vis[t]) return 0;
		vis[t] = 1;
		nxt = 0;
		while(t) {
			nxt = nxt + (t % 10) * (t % 10);
			t /= 10;
		}
		if (nxt == 1) return 1;
		t = nxt;
//		printf("t = %d\n", t);
	}while(t != x);
	return 0;
}

int main(){
	int T, t;
	scanf("%d", &T);
	while(T --) {
		scanf("%d", &t); printf("%d ", t);
		scanf("%d", &t); printf("%d ", t);
		puts(check(t) ? "YES" : "NO");
	}
	return 0;
}
