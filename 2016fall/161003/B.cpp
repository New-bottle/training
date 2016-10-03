#include<cstdio>
#include<map>
#include<queue>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int N = 100010;
const LL INF = 1e18;

int to[N << 1], nxt[N << 1], head[N], cnt, col[N << 1];
LL len[N << 1];
void ins(int x, int y, int z, int c) {
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt; len[cnt] = z; col[cnt] = c;
}
void add(int x, int y, int z, int c) {
	ins(x, y, z, c); ins(y, x, z, c);
}

typedef pair<LL,int> pii;
//map<int,LL> d[N];
pii d[N][2];

int S, n, m, q;
bool inq[N];
void solve() {
	for(int i = 1; i <= n; i ++)
		d[i][0].first = d[i][1].first = INF;
	queue<int>Q;
	d[S][0].first = d[S][1].first = 0;
	Q.push(S); inq[S] = 1;
	while(!Q.empty()) {
		int x = Q.front(); Q.pop();
		inq[x] = 0;
		for(int i = head[x]; i; i = nxt[i]) {
			LL now = (col[i] == d[x][0].second ? d[x][1].first : d[x][0].first);
			if (now == INF) continue;
//			printf("x = %d now = %lld\n", x, now);
			int y = to[i];
			if (d[y][0].first > len[i] + now) {
				swap(d[y][0], d[y][1]);
				d[y][0].first = len[i] + now;
				d[y][0].second = col[i];
				if (!inq[y]) {
					inq[y] = 1;
					Q.push(y);
				}
			} else if (d[y][1].first > len[i] + now && d[y][0].second != col[i]) {
				d[y][1].first = len[i] + now;
				d[y][1].second = col[i];
				if (!inq[y]) {
					inq[y] = 1;
					Q.push(y);
				}
			}
		}
	}
	for(int i = 1; i <= n; i ++) if (d[i][0].first == INF) 
		d[i][0].first = -1;
	for(int i = 1; i <= n; i ++)
		printf("%lld %d %lld %d\n", d[i][0].first, d[i][0].second, d[i][1].first, d[i][1].second);
}

int main(){
	int m, C;
	scanf("%d%d%d", &n, &m, &C);
	for(int i = 1; i <= m; i ++) {
		int x, y, l, c;
		scanf("%d%d%d%d", &x, &y, &l, &c);
		add(x, y, l, c);
	}
	scanf("%d%d", &S, &q);
	solve();
	for(int i = 1; i <= q; i ++) {
		int t;
		scanf("%d", &t);
		printf("%lld\n", d[t][0].first);
	}
	return 0;
}
