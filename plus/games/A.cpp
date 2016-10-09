#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 110;

int n, a[N];
int gcd(int a, int b) {return b ? gcd(b, a % b) : a;}
int main(){
	scanf("%d", &n);
	int d;
	for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
	d = a[1];
	for(int i = 2; i <= n; i ++) d = gcd(d, a[i]);
	for(int i = 1; i <= n; i ++) a[i] /= d;
	sort(a + 1, a + n + 1);
	if ((a[n] - n) & 1) puts("Alice");
	else puts("Bob");
	return 0;
}
