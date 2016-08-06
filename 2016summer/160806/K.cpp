#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1010;
char s[N];
int f[N][2], a[N];

int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	for(int i = 1; i <= n; i ++) a[i] = (s[i] == '3');
	memset(f, 0x3f, sizeof f);
	f[0][1] = 0;
	for(int i = 1; i <= n; i ++){
		if (a[i]){
			f[i][1] = min(f[i][1], f[i - 1][1]);
			f[i][0] = min(f[i][0], f[i - 1][0] + 1);
		}else{
			f[i][0] = min(f[i - 1][0], f[i - 1][1]);
			f[i][1] = min(f[i][1], f[i - 1][1] + 1);
		}
	}
	printf("%d\n", min(f[n][0], f[n][1]));
	return 0;
}
