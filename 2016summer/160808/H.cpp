#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

int rg[12];
int main(){
	for(int i = 1; i <= 10; i ++) rg[i] = (20 * i) * (20 * i);
	int T;
	scanf("%d", &T);
	int n, x, y;
	while(T --){
		scanf("%d", &n);
		int ans = 0;
		for(int i = 1; i <= n; i ++){
			scanf("%d%d", &x, &y);
			int dis = x * x + y * y;
			for(int j = 1; j <= 10; j ++)
				if (dis <= rg[j]){
					ans += (11 - j);
					break;
				}
		}
		printf("%d\n", ans);
	}
	return 0;
}
