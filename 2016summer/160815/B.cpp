#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#define LL long long
#define MOD 110119
#define N 1100
using namespace std;
LL fac[MOD * 10 + 10], inv[MOD * 10 + 10], n, m;
int r;
LL q_pow(LL a, int b){
	LL res = 1;
	while(b){
		if(b & 1) res = res * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	return res;
}
LL x[N], y[N], f[N][2];
struct node{
	LL x, y;
	node(){}
	node(LL a, LL b){
		x = a;
		y = b;
	}
	friend bool operator < (const node &a, const node &b){
		return a.x == b.x ? a.y < b.y : a.x < b.x;
	}
	friend bool operator == (const node &a, const node &b){
		return (a.x == b.x) && (a.y == b.y);
	}
}data[N];
LL C(LL a, LL b){
	if (a < 0 || b < 0) return 0;
	if(a < b) return 0;
	if(a < MOD && b < MOD) return fac[a] * inv[b] % MOD * inv[a - b] % MOD;
	return C(a / MOD, b / MOD) * C(a % MOD, b % MOD) % MOD;
}
void solve(){
	int cnt = 0;
	bool flag = 0;
	for(int i = 1; i <= r; i ++){
		LL tmpx, tmpy;
		//scanf("%lld%lld", &tmpx, &tmpy);
		std::cin >> tmpx >> tmpy;
		if((tmpx == n && tmpy == m) || (tmpx == 1 && tmpy == 1)){
			flag = 1;
		}
		if(tmpx <= 1 || tmpy <= 1) continue;
		if((tmpx * 2 - tmpy - 1) % 3 == 0 && (tmpy * 2 - tmpx - 1) % 3 == 0){
			++ cnt;
			x[cnt] = tmpx;
			y[cnt] = tmpy;
		}
	}
	if(flag){
		puts("0");
		return;
	}
	r = cnt;
	//cout << r << endl;
	x[0] = y[0] = 1;
	if((n * 2 - m - 1) % 3 != 0 || (m * 2 - n - 1) % 3 != 0){
		puts("0");
		return;
	}
	if(n == 1 && m == 1){
		puts("1");
		return;
	}
	x[r + 1] = n;
	y[r + 1] = m;
	//cout << "?" << endl;
	//cout << r << endl;
	//for(int i = 0; i <= r + 1; i ++) cout << x[i] << ' ' << y[i] << endl;
	
	for(int i = 0; i <= r + 1; i ++) data[i] = node(x[i], y[i]);
	cnt = r + 2;
	sort(data, data + cnt);
	cnt = unique(data, data + cnt) - data;
	//cout << cnt << endl;
	r = cnt - 2;
	for(int i = 0; i <= r + 1; i ++){
		x[i] = data[i].x;
		y[i] = data[i].y;
	}
	
	memset(f, 0, sizeof(f));
	f[0][0] = MOD - 1;
	f[0][1] = 0;
	for(int i = 0; i <= r; i ++){
		for(int j = i + 1; j <= r + 1; j ++){
			if(j == i || x[j] <= x[i] || y[j] <= y[i]) continue;
			LL tmpx = x[j] - x[i] + 1;
			LL tmpy = y[j] - y[i] + 1;
			if((tmpx * 2 - tmpy - 1) % 3 != 0 || (tmpy * 2 - tmpx - 1) % 3 != 0) continue;
			LL cntx = (tmpx * 2 - tmpy - 1) / 3, cnty = (tmpy * 2 - tmpx - 1) / 3;
			LL tmpc = C(cntx + cnty, cntx);
			//cout << cntx << ' ' << cnty << ' ' << i << ' ' << j << endl;
			f[j][0] = (f[j][0] + (MOD - f[i][1]) * tmpc) % MOD;
			f[j][1] = (f[j][1] + (MOD - f[i][0]) * tmpc) % MOD;
		}
	}
	
	//printf("%lld\n", (f[r + 1][1] + f[r + 1][0]) % MOD);
	cout << (f[r + 1][1] + f[r + 1][0]) % MOD << endl;
}
int main(){
	fac[0] = fac[1] = inv[0] = inv[1] = 1;
	for(int i = 2; i < MOD; i ++) fac[i] = fac[i - 1] * i % MOD;
	inv[MOD - 1] = q_pow(fac[MOD - 1], MOD - 2);
	for(int i = MOD - 2; i; i --) inv[i] = inv[i + 1] * (i + 1) % MOD;
	for(int i = 1; cin >> n >> m >> r; i ++){
		printf("Case #%d: ", i);
		solve();
		//cout << endl;
	}
	return 0;
}
