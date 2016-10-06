#include<array>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#define N 10010
#define MOD 1000000007
using namespace std;
int len, fac[N];
struct matrix{
	vector<array<int, 510> > f;
	matrix(){f.resize(510);for(int i = 0; i < 510; ++i) memset(f[i].data(), 0, sizeof(f[i]));}
	friend matrix operator * (const matrix &a, const matrix &b){
		matrix ans;
		for(int i = 0; i <= len + 1; i ++){
			for(int k = 0; k <= len + 1; k ++){
				if(a.f[i][k]){
					for(int j = 0; j <= len + 1; j ++){
						ans.f[i][j] = (1LL * a.f[i][k] * b.f[k][j] + ans.f[i][j]) % MOD;
					}
				}
			}
		}
		return ans;
	}
	friend matrix operator + (const matrix &a, const matrix &b){
		matrix ans;
		for(int i = 0; i <= len + 1; i ++){
			for(int j = 0; j <= len + 1; j ++){
				ans.f[i][j] = (a.f[i][j] + b.f[i][j]) % MOD;
			}
		}
		return ans;
	}
}A, one;
char str[N];
struct bign{
	int f[N], len;
	void read(){
		scanf("%s", str);
		len = strlen(str);
		for(int i = 0; i < len; i ++){
			f[len - i] = str[i] - '0';
		}
	}
	friend bign operator - (bign a, const int b){
		a.f[1] -= b;
		if(a.f[1] >= 0) return a;
		else{
			a.f[1] = a.f[1] + 10;
			int k = 0;
			for(int i = 2; i <= a.len && k == 0; i ++){
				a.f[i] = a.f[i] - 1 + k + 10;
				k = a.f[i] / 10;
				a.f[i] %= 10;
			}
		}
		return a;
	}
	bool is_zero(){
		return (len == 1 && f[1] == 0);
	}
}L, R;
char C[N];

int nxt[N];
void init(){
	len = strlen(C + 1);
	int j = 0;
	nxt[1] = 0;
	for(int i = 2; i <= len; i ++){
		while(j && C[i] != C[j + 1]) j = nxt[j];
		if(C[i] == C[j + 1]) j ++;
		nxt[i] = j;
	}
	
	A.f[0][1] = 1;
	A.f[0][0] = 1;
	for(int i = 1; i <= len; i ++){
		for(int j = '0'; j <= '9'; j ++){
			int k = i;
			while(k && j != C[k + 1]) k = nxt[k];
			if(j == C[k + 1]) A.f[i][k + 1] ++;
		}
	}
	A.f[len][len + 1] = 1;
	A.f[len + 1][len + 1] = 1;
	
	for(int i = 0; i <= len + 1; i ++) one.f[i][i] = 1;
	
	for(int i = fac[0] = 1; i <= N - 1; i ++) fac[i] = 1LL * fac[i - 1] * 10 % MOD;
}

matrix quick_pow(matrix m, int n){
	matrix res = one;
	while(n){
		if(n & 1) res = res * m;
		n >>= 1;
		m = m * m;
	}
	return res;
}

matrix dp(int n){
	if(n == 0) return one;
	if(n == 1) return A;
	if(n & 1){
		int n1 = n / 2;
		return dp(n1) * (quick_pow(A, n1 + 1) + one);
	}
	else return dp(n - 1) * A + one;
}

int kmp(const bign &cur, int l, int r){
	int j = 0, res = 0;
	for(int i = l; i >= r; i --){
		while(j && cur.f[i] + '0' != C[j + 1]) j = nxt[j];
		if(cur.f[i] + '0' == C[j + 1]) j ++;
		if(j == len){
			res ++;
			j = nxt[j];
		}
	}
	return res;
}

char B[N];
int calc(const bign &num){
	matrix res;
	int ans = 0;
	res.f[0][0] = 1;
	res = res * dp(num.len);
	for(int i = 0; i <= len + 1; i ++){
		for(int j = 0; j <= len + 1; j ++){
			cout << res.f[i][j] << ' ';
		}
		cout << endl;
	}
	for(int i = num.len; i; i --){
		ans = ans + 1LL * kmp(num, num.len, i) * fac[i - 1] % MOD;
	}
	if(strcmp(C + 1, "0") == 0){
		for(int i = num.len; i; i --){
			ans = (ans - 1LL * (num.len - i) * 9 % MOD * fac[i - 1] % MOD + MOD) % MOD;
		}
	}
	return ans;
}

int main(){
	L.read();
	R.read();
	scanf("%s", C + 1);
	init();
	printf("%d\n", calc(R) - (L.is_zero() ? 0 : calc(L - 1)));
	return 0;
}
