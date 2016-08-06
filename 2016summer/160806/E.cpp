#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
int n, m;
int num = 100000, ans[40];
LL a[40], tar;
void jud(int mask){
	LL tmp = 0;
	int t = 0;
	for(int i = 0; i < n; i ++)
		if (mask >> i & 1){
			t ++;
			tmp |= a[i];
		}
	if ((tmp & tar) == tar){
		if (t < num){
			num = t;
			t = 0;
			for(int i = 0; i < n; i ++) if (mask >> i & 1)
				ans[++ t] = i + 1;
		}
	}
}

int main(){
//	freopen("input.txt","r",stdin);
//	freopen("output.txt","w",stdout);
	scanf("%d%d", &n, &m);
	tar = (1LL << m) - 1;

	int k, x;
	for(int i = 0; i < n; i ++){
		scanf("%d", &k);
		for(int j = 1; j <= k; j ++){
			scanf("%d", &x);
			a[i] |= (1LL << (x - 1));
		}
	}
	for(int i = 1; i < (1 << n); i ++)
		jud(i);
	printf("%d\n", num);
	for(int i = 1; i <= num; i ++)
		printf("%d%c", ans[i], i == num ? '\n' : ' ');
	return 0;
}
