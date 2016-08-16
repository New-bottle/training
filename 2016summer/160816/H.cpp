#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#define N 20
using namespace std;
int f[N][N];
int a[N];
void solve(int n){
	a[0] = a[n + 1] = 0;
	for(int i = 1; i <= n; i ++) a[i] = i;
	do{
		int t = 0;
		for(int i = 1; i <= n; i ++){
			if(a[i] > a[i - 1] && a[i] > a[i + 1]){
				t ++;
			}
		}
		f[n][t] ++;
	}while(next_permutation(a + 1, a + n + 1));

}
int main(){
	memset(f, 0, sizeof(f));
	for(int i = 1; i <= 10; i ++){
		solve(i);
	}
	
	for(int i = 1; i <= 10; i ++){
		for(int j = 1; j <= 10; j ++){
			printf("(%2d%2d) = %6d ", i, j, f[i][j]);
		}	
		cout << endl;
	}
	return 0;
}
