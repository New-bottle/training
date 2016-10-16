#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;
int n, a, b;
int gcd(int a, int b) {return b ? gcd(b, a % b) : a;}

int main(){
	int T, cs = 0;
	scanf("%d", &T);
	while(T --) {
		printf("Case #%d: ", ++ cs);
		scanf("%d%d%d", &n, &a, &b);
		int d = gcd(a, b);
		n /= d;
		n -= 2;
		puts(n & 1 ? "Yuwgna" : "Iaka");
	}
	return 0;
}
