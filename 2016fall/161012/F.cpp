#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 1000010
#define MOD 1000000009
using namespace std;
const int LL = 0, LE = 1, EL = 2, EE = 3, E = 1, L = 0;
char a[N], b[N], c[N];
long long dp[N][4];

long long update(char a, char b, char c, int kind){
	if(kind == LL){
		if(a != '?' && b != '?' && c != '?') return (a < b && b < c);
		if(a != '?' && b != '?' && c == '?') return (int)('z' - b) * (a < b);
		if(a != '?' && b == '?' && c != '?') return (int)(c - a - 1) * (a < c);
		if(a != '?' && b == '?' && c == '?') return (int)('z' - a) * ('z' - a - 1) / 2;
		if(a == '?' && b != '?' && c != '?') return (int)(b - 'a') * (b < c);
		if(a == '?' && b != '?' && c == '?') return (int)(b - 'a') * ('z' - b);
		if(a == '?' && b == '?' && c != '?') return (int)(c - 'a') * (c - 'a' - 1) / 2;
		if(a == '?' && b == '?' && c == '?') return 2600;
	}
	else if(kind == LE){
		if(a != '?' && b != '?' && c != '?') return (a < b && b == c);
		if(a != '?' && b != '?' && c == '?') return (a < b);
		if(a != '?' && b == '?' && c != '?') return (a < c);
		if(a != '?' && b == '?' && c == '?') return (int)('z' - a);
		if(a == '?' && b != '?' && c != '?') return (int)(b - 'a') * (b == c);
		if(a == '?' && b != '?' && c == '?') return (int)(b - 'a');
		if(a == '?' && b == '?' && c != '?') return (int)(c - 'a');
		if(a == '?' && b == '?' && c == '?') return 325;
	}
	else if(kind == EL){
		if(a != '?' && b != '?' && c != '?') return (a == b && b < c);
		if(a != '?' && b != '?' && c == '?') return (int)('z' - a) * (a == b);
		if(a != '?' && b == '?' && c != '?') return (int)(a < c);
		if(a != '?' && b == '?' && c == '?') return (int)('z' - a);
		if(a == '?' && b != '?' && c != '?') return (int)(b < c);
		if(a == '?' && b != '?' && c == '?') return (int)('z' - b);
		if(a == '?' && b == '?' && c != '?') return (int)(c - 'a');
		if(a == '?' && b == '?' && c == '?') return 325;
	}
	else if(kind == EE){
		if(a != '?' && b != '?' && c != '?') return (a == b && b == c);
		if(a != '?' && b != '?' && c == '?') return (a == b);
		if(a != '?' && b == '?' && c != '?') return (a == c);
		if(a != '?' && b == '?' && c == '?') return 1;
		if(a == '?' && b != '?' && c != '?') return (b == c);
		if(a == '?' && b != '?' && c == '?') return 1;
		if(a == '?' && b == '?' && c != '?') return 1;
		if(a == '?' && b == '?' && c == '?') return 26;
	}
}
long long update(char a, char b, int kind){
	if(kind == E){
		if(a == '?' && b == '?') return 26;
		if(a == '?' && b != '?') return 1;
		if(a != '?' && b == '?') return 1;
		if(a != '?' && b != '?') return (a == b);
	}
	else{
		if(a == '?' && b == '?') return 325;
		if(a == '?' && b != '?') return b - 'a';
		if(a != '?' && b == '?') return 'z' - a;
		if(a != '?' && b != '?') return (a < b);
	}
}
long long update(char c){
	if(c == '?') return 26;
	return 1;
}

void solve(){
	scanf("%s", a + 1);
	scanf("%s", b + 1);
	scanf("%s", c + 1);
	int len1 = strlen(a + 1);
	int len2 = strlen(b + 1);
	int len3 = strlen(c + 1);
	int n = max(len1, max(len2, len3));
	
	for(int i = len1 + 1; i <= n; i ++) a[i] = 'a';
	for(int i = len2 + 1; i <= n; i ++) b[i] = 'a';
	for(int i = len3 + 1; i <= n; i ++) c[i] = 'a';
	
	for(int i = 1; i <= n; i ++){
		for(int j = 0; j < 4; j ++){
			dp[i][j] = 0;
		}
	}
	dp[0][EE] = 1;
	for(int i = 1; i <= n; i ++){
		dp[i][LL] += dp[i - 1][EE] * update(a[i], b[i], c[i], LL) % MOD;
		dp[i][LL] += dp[i - 1][EL] * update(a[i], b[i], L) % MOD * update(c[i]) % MOD;
		dp[i][LL] += dp[i - 1][LE] * update(a[i]) % MOD * update(b[i], c[i], L) % MOD;
		dp[i][LL] += dp[i - 1][LL] * update(a[i]) % MOD * update(b[i]) % MOD * update(c[i]) % MOD;
		dp[i][LL] %= MOD;
		
		dp[i][EL] += dp[i - 1][EE] * update(a[i], b[i], c[i], EL) % MOD;
		dp[i][EL] += dp[i - 1][EL] * update(a[i], b[i], E) % MOD * update(c[i]) % MOD;
		dp[i][EL] %= MOD;
		
		dp[i][LE] += dp[i - 1][EE] * update(a[i], b[i], c[i], LE) % MOD;
		dp[i][LE] += dp[i - 1][LE] * update(a[i]) % MOD * update(b[i], c[i], E) % MOD;
		dp[i][LE] %= MOD;
		
		dp[i][EE] = dp[i - 1][EE] * update(a[i], b[i], c[i], EE) % MOD;
	}
	
	printf("%lld\n", (dp[n][LL] + (len2 < len3 ? dp[n][LE] : 0) + (len1 < len2 ? dp[n][EL] : 0) + (len1 < len2 && len2 < len3 ? dp[n][EE] : 0)) % MOD);
}
int main(){
	int testcase;
	scanf("%d", &testcase);
	while(testcase --){
		solve();
	}
	return 0;
}
