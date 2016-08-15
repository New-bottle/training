#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1010;
int sg[N], n = 1000, a[N];
bool vis[N];

void init() {
	sg[0] = 0;
	for(int i = 1; i <= 100; i ++) {
		memset(vis, 0, sizeof vis);
		for(int j = 0; j < i; j ++) vis[sg[j]] = 1;
		for(int x = 1; x <= i; x ++) {
			for(int y = 1; y <= i; y ++)
				if (i - x - y > 0)
					vis[sg[x] ^ sg[y] ^ sg[i - x - y]] = 1;
		}
		for(int j = 0; j <= n; j ++)
			if (!vis[j]) {
				sg[i] = j;
				break;
			}
		if (sg[i] != i) printf("sg[%d] = %d\n",i, sg[i]);
	}
}
int main(){
//	init();
	int T;
	scanf("%d", &T);
	while(T --) {
		scanf("%d", &n);
		int ans = 0, x;
		for(int i = 1; i <= n; i ++) {
			scanf("%d", &x);
			if (x % 8 == 0) ans ^= x - 1;
			else if (x % 8 == 7) ans ^= x + 1;
			else ans ^= x;
		}
		printf(ans ? "First " : "Second ");
		puts("player wins.");
	}
	return 0;
}
