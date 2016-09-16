#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long double ldb;
const ldb pi = acos(-1);

int n;

int main(){
	int cs = 0;
	while(scanf("%d",&n) != EOF && n) {
		printf("Menu %d: ", ++ cs);

		ldb mn = 1e10;
		int ans = 0, d, c;
		for(int i = 1; i <= n; i ++) {
			scanf("%d%d", &d, &c);
			if (c / (pi * d * d) * 4.0 < mn) {
				mn = c / (pi * d * d) * 4.0;
				ans = d;
			}
		}
		printf("%d\n", ans);
	}

	return 0;
}
