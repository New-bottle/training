#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
LL n;
void work(){
	LL ans = 0;
	for(LL i = 1; i * i * i <= n; i ++)
		for(LL j = i; i * j * j <= n; j ++){
			LL t = n / (i * j);
			LL v = (t - j) * 6;
			if (i == j) v /= 2, ans += 1;
			else ans += 3;
			ans += v;
		}
	cout << ans << endl;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int cs = 0;
	while(cin >> n){
		cout << "Case " << ++ cs << ": ";
		work();
	}
	return 0;
}
