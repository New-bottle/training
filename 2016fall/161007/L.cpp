#include<cstdio>
#include<algorithm>
#include<iostream>
#define LL long long
using namespace std;
int main(){
	int testcase;
	scanf("%d", &testcase);
	for(int i = 1; i <= testcase; i ++){
		int k;
		scanf("%d", &k);
		LL ans = 0;
		for(int j = 1; j <= k; j ++){
			ans = ans * 2 + 1;
		}
		printf("%lld\n", ans);
	}
}
