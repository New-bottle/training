#include<cstdio>
#include<queue>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 200010;
typedef long long LL;

int a[N], n;
LL s[N], f[N];
//priority_queue<LL, vector<LL>, greater<LL> >Q;
priority_queue<LL>Q;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) {
		scanf("%d", &a[i]);
		s[i] = s[i - 1] + a[i];
	}
//	for(int i = 1; i <= n; i ++) printf("%lld ", s[i]); puts("");
	f[n] = s[n];
	Q.push(f[n]);
	LL ans = f[n];
	for(int i = n - 1; i > 1; i --) {
//		printf("Q.top() = %lld, f[i] = %lld\n", Q.top(), s[i] - Q.top());
		f[i] = s[i] - Q.top();
		Q.push(f[i]);
		ans = max(ans, f[i]);
	}
	printf("%lld\n", ans);
	return 0;
}
