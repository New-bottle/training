#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1000010;
int n, m, f[N], a[N];

int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++){
		scanf("%d", &a[i]);
		a[i] &= 1;
		a[i] ^= 1;
	}
	int ans = 0;
	for(int i = 1; i <= n; i ++) 
		ans = ans ^ a[i];
	puts(ans ? "Constantine" : "Mike");
	return 0;
}
