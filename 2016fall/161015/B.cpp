#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;

int n, m, x[N], a;

int main(){
	scanf("%d%d", &n, &a);
	for(int i = 1; i <= n; i ++) scanf("%d", &x[i]);
	if (n == 1) {
		puts("0");
		return 0;
	}
	sort(x + 1, x + n + 1);
	int ans = 1e9;
	ans = min(ans, abs(a - x[1]) + abs(x[1] - x[n - 1]));
	ans = min(ans, abs(a - x[n - 1]) + abs(x[1] - x[n - 1]));
	ans = min(ans, abs(a - x[2]) + abs(x[2] - x[n]));
	ans = min(ans, abs(a - x[n]) + abs(x[2] - x[n]));
	printf("%d\n", ans);
	return 0;
}
