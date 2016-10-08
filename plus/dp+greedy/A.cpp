#include<cstdio>
#include<queue>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 200010;
typedef pair<int,int> pii;

int n, s, cnt;
pii e[N], tmp[N];
priority_queue<pii >Q;

bool solve() {
	while(!Q.empty()) {
		int x = Q.top().second, num = Q.top().first; Q.pop();
		int tot = 0;
//		printf("x = %d y = ", x);
		for(int i = 1; i <= num; i ++) {
			if (Q.empty()) return 0;
			int y = Q.top().second, t = Q.top().first; Q.pop();
//			printf("%d ", y);
			if (t - 1) {
				tmp[++ tot] = make_pair(t - 1, y);
			}
			e[++ cnt] = make_pair(x, y);
		}
		for(int i = 1; i <= tot; i ++) Q.push(tmp[i]);
//		puts("");
	}
	return 1;
}
int main(){
	scanf("%d%d", &n, &s);
	for(int i = 1; i <= n; i ++) {
		int x;
		scanf("%d", &x);
		if (x) Q.push(make_pair(x, i));
	}
	if (s & 1) {
		puts("No");
		return 0;
	}
	if (solve()) {
		puts("Yes");
		printf("%d\n", cnt);
		for(int i = 1; i <= cnt; i ++)
			printf("%d %d\n", e[i].first, e[i].second);
	} else {
		puts("No");
	}
	return 0;
}
