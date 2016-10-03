#include<cstdio>
#include<map>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;
typedef long long LL;

map<LL, int>mpx, mpy;
LL x[N], y[N];
int v1[N], v2[N], n;

int main(){
	scanf("%d", &n);
	int tx = 0, ty = 0;
	for(int i = 1; i <= n; i ++) {
		scanf("%lld%lld%d%d", &x[i], &y[i], &v1[i], &v2[i]);
		if (mpx[x[i]]) x[i] = mpx[x[i]];
		else mpx[x[i]] = ++ tx, x[i] = tx;
		if (mpy[y[i]]) y[i] = mpy[y[i]];
		else mpy[y[i]] = ++ ty, y[i] = ty;
	}
	
	return 0;
}
