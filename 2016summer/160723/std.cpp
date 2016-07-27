#include <bits/stdc++.h>
using namespace std;

const int dx[4] = {1, 0, -1, 0},
		  dy[4] = {0, 1, 0, -1};
const int N = 15;
int n, m, cc, cc_T;
int d[N<<N-1], dis[N][N];
int label[N][N], label_T[N][N];
bool block[N][N], ba[N][N], sw[N][N];

struct P {
	int x, y;
	__inline P(int x=0, int y=0): x(x), y(y) {}
	__inline bool valid() {
		return x >= 0 && y >= 0 && x < n && y < m;
 	}
} T[N+1];

struct S {
	int p, s;
	__inline S(int p=0, int s=0): p(p), s(s) {}
	__inline int shift() {
		return (p<<14) + s;
	}
};

char buf[N + 5];
int full_Y;

P BFS_Q[N*N];
int BFS_dis[N][N];
void BFS(P s) {
	int l = 0, r = 0; BFS_Q[r++] = s; 
	memset(BFS_dis, -1, sizeof(BFS_dis));
	BFS_dis[s.x][s.y] = 0;
	for (; l < r; ) {
		P u = BFS_Q[l++]; int d0 = BFS_dis[u.x][u.y];
		for (int d = 0; d < 4; d++) {
			P v = P(u.x+dx[d], u.y+dy[d]);
			if (v.valid() && !block[v.x][v.y] && !~BFS_dis[v.x][v.y]) {
				BFS_dis[v.x][v.y] = d0 + 1;
				BFS_Q[r++] = v;
			}
		}
	}
}

S Q[N<<N-1];
bool inq[N<<N-1];
bool SPFA(int s, int w, int full_Y) {
	S ss = S(s, 0);
	int mod = (cc_T+1) <<cc_T;
	int l = 0, r = 0; Q[r++] = ss; 
	memset(d, -1, sizeof d);
	memset(inq, 0, sizeof inq);
	*(d + ss.shift()) = w;
	*(inq + ss.shift()) = 1;
	for (; l != r; ) {
		S u = Q[l++]; l %= mod;
		*(inq + u.shift()) = 0;
		//cout << u.p << " " << bitset<7>(u.s) << endl;
		int d0 = *(d + u.shift()), tmp = ~u.s & ((1<<cc_T)-1);
		for (int sj = tmp&(-tmp); tmp; tmp ^= sj, sj = tmp&(-tmp)) {
			int j = __lg(sj); //printf("%d\n", j);
			S v = S(j, u.s ^ (1<<j)); int *dv = d+v.shift();
			if (~dis[u.p][j] && d0-dis[u.p][j] > *dv) {
				*dv = ba[T[j].x][T[j].y] ? w : d0-dis[u.p][j];
				if ((v.s | full_Y) == v.s) return 1;
				if (!*(inq+ v.shift())) {
					*(inq+ v.shift()) = 1;
					Q[r++] = v;
					r %= mod;
				}
			}
		}
	}
	return 0;
}

int main() {
	freopen("B.in","r",stdin);
	for (; scanf("%d%d", &n, &m), n || m; ) {
		cc = cc_T = full_Y = 0;
		P st;
		for (int i = 0; i < n; i++) {
			scanf("%s", buf);
			for (int j = 0; j < m; j++) {
				label[i][j] = cc++;
				block[i][j] = ba[i][j] = sw[i][j] = 0;
				label_T[i][j] = -1;
				if (buf[j] == 'F') {
					st = P(i,j);
				}
				else if (buf[j] == 'G') {
					ba[i][j] = 1;
					label_T[i][j] = cc_T;
					T[cc_T++] = P(i,j);
				}
				else if (buf[j] == 'D') {
					block[i][j] = 1;
				}
				else if (buf[j] == 'Y') {
					sw[i][j] = 1;
					full_Y ^= 1<<cc_T;
					label_T[i][j] = cc_T;
					T[cc_T++] = P(i,j);
				} 
			}
		}
		
		//assert(cc_T < 15);
		//cout << cc_T << " " << bitset<N>(full_Y) << endl;
		
		//puts("done");
		if (!full_Y) {
			puts("0");
			continue;
		}
		BFS(st);
		for (int j = 0; j < n; j++)
			for (int k = 0; k < m; k++)
				if (~label_T[j][k]) {
					dis[cc_T][label_T[j][k]] = BFS_dis[j][k];
					//printf("%d %d\n", label_T[j][k], BFS_dis[j][k]);
				}
		
		for (int i = 0; i < cc_T; i++) {
			BFS(T[i]);
			for (int j = 0; j < n; j++)
				for (int k = 0; k < m; k++)
					if (~label_T[j][k])
						dis[i][label_T[j][k]] = BFS_dis[j][k];
		}
		
		//puts("done");
		int l = 0, r = n*m;
		for (; l < r - 1; ) {
			int mid = l + r >> 1;
			if (SPFA(cc_T, mid, full_Y))
				r = mid;
			else l = mid;
		}
		if (SPFA(cc_T, r, full_Y)) printf("%d\n", r);
		else puts("-1");
	}
	
	return 0;
}
