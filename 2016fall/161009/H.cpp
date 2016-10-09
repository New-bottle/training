#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#define N 10090
#define MOD 10007
using namespace std;
int ans[N];
char str[N];
bool check(int x){
	return (str[x] == 'h' && str[x + 1] == 'e' && str[x + 2] == 'h' && str[x + 3] == 'e');
}
void solve(){
	memset(ans, 0, sizeof(ans));
	scanf("%s", str + 1);
	ans[0] = 1;
	int n = strlen(str + 1);
	for(int i = 1; i <= n; i ++){
		ans[i] = ans[i - 1];
		if(i >= 4 && check(i - 3)) ans[i] =(ans[i] + ans[i - 4]) % MOD;
	}
	printf("%d\n", ans[n]);
}
int main(){
	int testcase;
	scanf("%d", &testcase);
	for(int i = 1; i <= testcase; i ++){
		printf("Case %d: ", i);
		solve();
	}
	return 0;
}
