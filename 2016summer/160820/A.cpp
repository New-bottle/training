#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

int a[100];

int main(){
	int T, t;
	scanf("%d", &T);
	while(T --) {
		scanf("%d", &t);
		printf("%d ", t);
		int ans = 0;
		for(int i = 1; i <= 20; i ++) scanf("%d", &a[i]);
		for(int i = 1; i <= 20; i ++)
			for(int j = 1; j < i; j ++)
				if (a[j] > a[i]) ans ++;
		printf("%d\n", ans);
	}
	return 0;
}
