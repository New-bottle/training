#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int P = 1e9 + 7;
const int N = 100010;
typedef long long LL;
LL Pow(LL a, LL b){
	LL r = 1;
	while(b){
		if (b & 1) r = r * a % P;
		a = a * a % P;
		b >>= 1;
	}
	return r;
}
int n, a[N], b[N];
int main(){
	freopen("A.in","r",stdin);
	while(scanf("%d", &n) == 1){
		LL ans = 0;
		for(int i = 1; i <= n; i ++)
			scanf("%d %d", &a[i], &b[i]);
		for(int mask = 1; mask < (1 << n); mask ++){
			int mxa = 0, mxb = 0;
			for(int i = 1; i <= n; i ++)
				if (mask >> (i - 1) & 1){
					mxa = max(mxa, a[i]);
					mxb = max(mxb, b[i]);
				}
			ans = (ans + Pow(2, mxa) * Pow(3, mxb) % P) % P;
		}
		printf("%lld\n",ans);
	}
	return 0;
}

