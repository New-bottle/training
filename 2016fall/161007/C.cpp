#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#define LL long long
#define N 100010
using namespace std;
vector< pair<LL, int> > block[N];
LL data[N];
int n;
LL gcd(LL a, LL b){
	LL c;
	while(b){
		c = a;
		a = b;
		b = c % b;
	}
	return a;
}
void solve(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) block[i].clear();
	for(int i = 1; i <= n; i ++){
		scanf("%lld", &data[i]);
	}
	
	block[n].push_back(make_pair(data[n], n));
	for(int i = n - 1; i; i --){
		int sz = block[i + 1].size();
		for(int j = 0; j < sz; j ++){
			LL tmp = gcd(data[i], block[i + 1][j].first);
			if(block[i].empty() || tmp != (block[i].end() - 1) -> first){
				block[i].push_back(make_pair(tmp, block[i + 1][j].second));
			}
		}
		if(data[i] != (block[i].end() - 1) -> first) block[i].push_back(make_pair(data[i], i));
	}
	
	LL ans = 0;
	for(int i = 1; i <= n; i ++){
		int sz = block[i].size();
		for(int j = 0; j < sz; j ++){
			ans = max(ans, block[i][j].first * (block[i][j].second - i + 1));
		}
	}
	printf("%lld\n", ans);
}
int main(){
	int testcase;
	scanf("%d", &testcase);
	while(testcase --){
		solve();
	}
	return 0;
}
