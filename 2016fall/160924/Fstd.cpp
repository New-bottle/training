#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 601000;
typedef long long LL;

int n, a[N], b[N];
int main(){
	int T;
	scanf("%d", &T);
	while(T --) {
		scanf("%d" ,&n);
		for(int i = 0; i < n; i ++) scanf("%d" ,&a[i]);
		for(int i = 0; i < n; i ++) scanf("%d", &b[i]);
		LL ans = 1e18;
		for(int st = 0; st < n; st ++) {
			LL tmp = 0;
			for(int i = 0; i < n; i ++)
				tmp += (LL)(a[i] - b[(st + i) % n]) * (LL)(a[i] - b[(st + i) % n]);
			ans = min(ans, tmp);
		}
		cout << ans << endl;
	}
	return 0;
}
