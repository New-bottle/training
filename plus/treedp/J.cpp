#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 5010;
int to[N << 1], nxt[N << 1], head[N], cnt;
void add(int x, int y) {
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
	to[++ cnt] = x; nxt[cnt] = head[y]; head[y] = cnt;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i < n; i ++) {
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	for
	return 0;
}
