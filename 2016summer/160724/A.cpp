#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;

int n, w[100010];
LL gcd(LL a, LL b){ return b ? gcd(b, a % b) : a;}
int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		LL sum = 0, tmp = 0, ans = n, d;
		for(int i = 1; i <= n; i ++){
			scanf("%d", &w[i]);
			sum += 1LL * w[i] * w[i];
			tmp += abs(w[i]);
		}
		tmp = sum * n - tmp * tmp;
		d = gcd(tmp, ans);
		printf("%I64d/%I64d\n",tmp / d, ans / d);
	}
	return 0;
}
