#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;

int n, b, d, a[N];
int main(){
	scanf("%d%d%d", &n, &b, &d);
	for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
	int now = 0, ans = 0;
	for(int i = 1; i <= n; i ++) {
		if (a[i] > b) continue;
		now += a[i];
		if (now > d) {
			now = 0;
			ans ++;
		}
	}
	printf("%d\n", ans);
	return 0;
}
