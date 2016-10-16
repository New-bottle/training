#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 200010;

int n, a[N];

bool check() {
	for(int i = 1; i <= n; i ++) {
		if (a[i] < 0) return 0;
		if (a[i] & 1) a[i + 1] --;
	}
	if (a[n + 1] < 0) return 0;
	return 1;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++ i) scanf("%d", &a[i]);
	if (check()) puts("YES");
	else puts("NO");
	return 0;
}
