#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef pair<int,int> pii;
const int N = 100010;
int to[N << 1], nxt[N << 1], head[N], cnt;
void add(int x, int y) {
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
	to[++ cnt] = x; nxt[cnt] = head[y]; head[y] = cnt;
}



int main(){
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 1; i < n; i ++) {
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	for(int i = 1; i <= m; i ++) {
		int x;
		scanf("%d", &x);
		have[x].push_back(i);
	}
	for(int i = 1; i <= q; i ++) {
		int opt;
		scanf("%d%d%d", &opt, &x, &y);
		if (opt == 1) {
			int k;
			scanf("%d", &k);
			for(int j = 1; j <= k; j ++) {
				s
			}
		}
	}
	return 0;
}
