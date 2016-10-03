#include<cstdio>
#include<queue>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;

typedef pair<int,int> pii;
int a[N], b[N], n, m;
int main(){
	scanf("%d%d", &n, &m);//n = 0 is possible
	for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
	for(int i = 1; i <= m; i ++) scanf("%d", &b[i]);
	sort(a + 1, a + n + 1);
	sort(b + 1, b + m + 1);
	queue<pii >Q;
	int mx = 1, now = 1;
	Q.push(make_pair(0,1));
	while(!Q.empty()) {
		int x = Q.front().first, num = Q.front().second; Q.pop();
		if (!x) {
			for(int i = 1; i <= num; i ++) 
				if (n) {
					Q.push(make_pair(1, a[n --]));
					now --;
				}else break;
		} else {
			if (!m) {
				now ++;
				mx = max(mx, now);
				continue;
			}
			for(int i = 1; i <= num; i ++)
				if (m) {
					Q.push(make_pair(0, b[m]));
					now += b[m];
					m --;
					mx = max(mx, now);
				} else break;
		}
	}
	printf("%d\n", mx);
	return 0;
}
