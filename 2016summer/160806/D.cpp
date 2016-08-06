#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
int n, k;
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d%d", &n, &k);
	int times = 0;
	LL now = 1;
	while(now < n){
		now = now * (1 + k);
		times ++;
	}
	printf("%d\n", times);
	return 0;
}
