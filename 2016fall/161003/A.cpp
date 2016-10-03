#include<cstdio>
#include<bitset>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 20010;
const int P = 1e9 + 7;
const int Limit = 1000000;
typedef long long LL;

int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};
int n, m, ans[N], a[N], cnt = 17;
int mul[N][17], now[17];

struct Bint {
	int v[10], len;
	Bint() {
		memset(v, 0, sizeof v);
		len = 1;
	}
	void print() {
		printf("%d", v[len]);
		for(int i = len - 1; i; i --) printf("%06d", v[i]);
	}
	int& operator [] (int x) {return v[x];}
	bool operator < (const Bint &b) const {
		if (len != b.len) return len < b.len;
		for(int i = len; i; i --) if (v[i] != b.v[i])
			return v[i] < b.v[i];
		return 0;
	}
	friend Bint operator * (const Bint &a, const int &b) {
		Bint c;
		int tmp = 0, len = a.len;
		for(int i = 1; i <= len; i ++) {
			c.v[i] = a.v[i] * b + tmp;
			tmp = c.v[i] / Limit;
			c.v[i] %= Limit;
		}
		while(tmp) {
			c[++ len] = tmp % Limit;
			tmp /= Limit;
		}
		c.len = len;
		return c;
	}
}b[N];

int Pow[17][12];
int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++) {
		scanf("%d", &a[i]);
		int tmp = a[i];
		for(int j = 0; j < 17; j ++)
			while(tmp % prime[j] == 0) {
				mul[i][j] ++;
				tmp /= prime[j];
			}
	}
	for(int i = 1; i <= n; i ++) b[i][b[i].len = 90] = 1;
	for(int i = 0; i < 17; i ++) {
		Pow[i][0] = 1;
		for(int j = 1; j <= 10; j ++) {
			Pow[i][j] = Pow[i][j - 1] * prime[i];
			if (Pow[i][j] * prime[i] > 60) break;
		}
	}
	for(int i = 1; i <= n; i ++) {
		Bint tmp; tmp[1] = 1;
		int t1 = 1;
		for(int k = 0; k < 17; k ++) now[k] = 0;
		for(int j = i; j <= n; j ++) {
			int len = j - i + 1;
			for(int k = 0; k < 17; k ++) if (mul[j][k] > now[k]) {
				tmp = tmp * Pow[k][mul[j][k] - now[k]];
				t1 = (LL)t1 * Pow[k][mul[j][k] - now[k]] % P;
				now[k] = mul[j][k];
			}
//			printf("i = %d j = %d t1 = %d len = %d  ", i, j, t1, len);
//			tmp.print(); puts("");
			if (tmp < b[len])
				b[len] = tmp, ans[len] = t1;
		}
	}

	for(int i = 1; i <= m; i ++) {
		int x;
		scanf("%d", &x);
		printf("%d\n", ans[x]);
	}
	return 0;
}
