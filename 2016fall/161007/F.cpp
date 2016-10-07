#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1010, M = 200010;
const int INF = 1e9;
const int dx[] = {1, 1, -1, -1},
	  	  dy[] = {1, -1, 1, -1};

struct edge {
	int from, to, v, c;
};
int flow, ans, n, m;

char s[13][13];
int id[13][13];
bool col[13][13];
inline bool inmap(int x, int y) {
	return (x > 0 && x < 11 && y > 0 && y < 11);
}
struct Net {
	edge E[M];
	int head[N], nxt[M], cnt;
	void ins(int x, int y, int z, int c) {
		E[++ cnt] = (edge){x, y, z, c};
		nxt[cnt] = head[x]; head[x] = cnt;
	}
	void add(int x, int y, int z, int c) {
		ins(x, y, z, c); ins(y, x, 0, -c);
	}
	int from[N], Q[M], d[N], S, T;
	bool inq[N];
	bool spfa() {
		int l = 0, r = -1;
		for(int i = 0; i <= T; i ++) d[i] = INF;
		d[S] = 0; Q[++ r] = S; inq[S] = 1;
		while(l <= r) {
			int x = Q[l ++];
			printf("%d\n", x);
			inq[x] = 0;
			for(int i = head[x]; i; i = nxt[i])
				if (E[i].v > 0 && d[x] + E[i].c < d[E[i].to]) {
					d[E[i].to] = d[x] + E[i].c;
					from[E[i].to] = i;
					if (!inq[E[i].to]) {
						Q[++ r] = E[i].to;
						inq[E[i].to] = 1;
					}
				}
		}
//		for(int i = 1; i <= T; i ++)
//			if (d[i] != INF) printf("d[%d] = %d\n", i, d[i]);
		return d[T] != INF;
	}
	void mcf() {
		int x = INF;
		for(int i = from[T]; i; i = from[E[i].from])
			x = min(x, E[i].v);
		for(int i = from[T]; i; i = from[E[i].from]) {
			E[i].v -= x;
			E[i ^ 1].v += x;
		}
		flow += x;
		ans += x * d[T];
	}
	void init() {
		memset(head, 0, sizeof head);
		S = 0; T = 102; cnt = 1;
		int ts = 101;
		add(S, ts, 1, 0);
		for(int i = 1; i <= 10; i ++) {
			scanf("%s", s[i] + 1);
			for(int j = 1; j <= 10; j ++)
				if (col[i][j] && s[i][j] == '#') {
					add(ts, id[i][j], 1, 0);
					add(id[i][j], T, 1, 0);
				}
		}
		for(int i = 1; i <= 10; i ++)
			for(int j = 1; j <= 10; j ++)
				if (col[i][j] && s[i][j] == '#')
					for(int k = 0; k < 4; k ++) {
						int tx = i + dx[k], ty = j + dy[k],
							nx = tx + dx[k], ny = ty + dy[k];
						if (!inmap(tx, ty) || !inmap(nx, ny)) continue;
						if (s[tx][ty] == 'B' && s[nx][ny] == '#') {
//							printf("(%d,%d) -> (%d,%d)\n", i, j, nx, ny);
							add(id[i][j], id[nx][ny], 1, -1);
						}
					}
		ans = flow = 0;
		while(spfa()) mcf();
		printf("%d\n", -ans);
	}
}G;

int main(){
	int T;
	scanf("%d", &T);
	int cnt = 0;
	for(int i = 1; i <= 10; i ++)
		for(int j = 1; j <= 10; j ++)
			col[i][j] = (i + j) & 1;
	for(int i = 1; i <= 10; i ++)
		for(int j = 1; j <= 10; j ++)
			id[i][j] = ++ cnt;
	while(T --) {
		G.init();
	}
	return 0;
}
