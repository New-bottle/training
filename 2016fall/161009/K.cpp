#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 110;

int a[N][N], n, m;
int main(){
	int T;
	scanf("%d", &T);
	while(T --) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++)
				scanf("%d", &a[i][j]);
		if  (a[n][m]) puts("Alice");
		else puts("Bob");
	}
	return 0;
}
