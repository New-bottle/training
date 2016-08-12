#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#define LL long long
#define N 21
using namespace std;
LL L, R;
int k;
int digit[20];
LL solve(LL x){
	if(x < 0) return 0;
	char str[21];
	sprintf(str, "%lld", x);
	int len = strlen(str);
	for(int i = 0; i < len; i ++) digit[i + 1] = str[i] - '0';
	
	int p = len + 1;
	for(int i = 1; i <= len; i ++){
		bool vis[10];
		memset(vis, 0, sizeof(vis));
		bool flag = 1;
		for(int j = max(1, i - k + 1); j <= len; j ++){
			if(vis[digit[j]] == 1){
				flag = 0;
				break;
			}
			vis[digit[j]] = 1;
		}
		if(!flag){
			p = i;
			break;
		}
	}
	
	LL ans = 1, res;
	for(int i = len; i >= p; i --) ans = ans * (10 - min(i - 1, k - 1));
	//cout << ans << endl;
	static int sum[N][10];
	for(int i = 1; i <= len; i ++){
		for(int j = 0; j < 10; j ++){
			sum[i][j] = sum[i - 1][j] + (digit[i] <= j);
		}
	}
	
	res = ans;
	while(-- p){
		res = res + ans * (digit[p] - (sum[p - 1][digit[p] - 1] - sum[max(0, p - k)][digit[p] - 1]));
		ans = ans * (10 - min(p - 1, k - 1));
	}
	
	cout << res << endl;
	return res;
}
int x[6];
int main(){
	while(scanf("%lld%lld%d", &L, &R, &k) == 3){
		printf("%lld\n", solve(R) - solve(L - 1));
	}
	return 0;
}
