#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int N = 9 * 18 * 9 + 5;
int lim[20];
LL f[20][20][2][N];

LL dfs(int pos, int piv, int up, int sum){
	if (!up && f[pos][piv][up][sum] != -1)
		return f[pos][piv][up][sum];
	if (sum < 0) return 0;
	if (pos == 0) return (sum == 0);
	int d = 0;
	if (up) d = lim[pos];
	else d = 9;
	LL tmp = 0;
	for(int i = 0; i <= d; i ++)
		tmp += dfs(pos - 1, piv, up && (i == d), sum + i * (pos - piv));
	if (!up) f[pos][piv][up][sum] = tmp;
	return tmp;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	memset(f, -1, sizeof f);
	int T;
	LL x, y;
	cin >> T;
	while(T--){
		cin >> x >> y;
		LL ans1 = 0, ans2 = 0;
		int len = 0;
		if (x){
			x --; len = 0;
			while(x){
				lim[++ len] = x % 10;
				x /= 10;
			}
			for(int i = 1; i <= len; i ++)
				ans2 += dfs(len, i, 1, 0);
			ans2 = ans2 - len + 1;
		}
		len = 0;
		while(y){
			lim[++ len] = y % 10;
			y /= 10;
		}
		for(int i = 1; i <= len; i ++)
			ans1 += dfs(len, i, 1, 0);
		ans1 = ans1 - len + 1;
		cout << ans1 - ans2 << endl;
	}
	return 0;
}
