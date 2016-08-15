#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
int p, q, ans;
int min0;


void dfs(int x, int last, int num, int step) {
	if (x == 0) ans = min(ans, step + max(0, q - num));
	if (x == 0) return;
	if (step > ans) return;
	if (x <= q) {
		ans = min(ans, step + max(0, q - x - num));
	}
	if (x + num <= q) return;
	int bu = last ? (last << 1) : 1;
	dfs(max(0, x - bu), bu, num, step + 1);
	if (max(0, x - bu) < q && last > 1){
		dfs(x, 0, num + 1, step + 1);
	}
	return;
}

void solve() {
	min0 = ans = 2e9;
	dfs(p, 0, 0, 0);
	printf("%d\n", ans);
}

int main(){
	int T;
	scanf("%d", &T);
	while(T --) {
		scanf("%d%d", &p, &q);
		solve();
	}
	return 0;
}
