#include<cstdio>
#include<queue>
#include<bitset>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int dx[] = {1, 1, -1, -1},
	  	  dy[] = {1, -1, 1, -1};
const int N = 15, M = 100010;
int to[M], nxt[M], head[55], cnt, tot;
void add(int x, int y) {
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
}

char s[N][N];
int id[N][N], mp[52][52], col[N][N];
pair<int,int> pos[110];

inline bool inmap(int x, int y) {
	return (x > 0 && x < 11 && y > 0 && y < 11);
}
int stx, sty;
void init() {
	memset(head, 0, sizeof head); cnt = 0;
	for(int i = 1; i <= 10; i ++)
		scanf("%s", s[i] + 1);
}

const int size = 52;
struct node {
	int x, y;
	bitset<size> mask;
};

queue<node> Q;

int bfs(int x, int y) {
	bitset<size> t = 0;
	int ans = 0;
	Q.push((node){x, y, t});
	while(!Q.empty()) {
		int x = Q.front().x, y = Q.front().y;
		bitset<size> mask = Q.front().mask, tmp; Q.pop();
		ans = max(ans, (int)mask.count());
		for(int i = 0; i < 4; i ++) {
			int tx = x + dx[i], ty = y + dy[i],
				nx = tx + dx[i], ny = ty + dy[i];
			if (s[tx][ty] != 'B') continue;
			if (!inmap(tx, ty) || !inmap(nx, ny)) continue;
			if (mask[id[tx][ty]] == 1 || s[nx][ny] != '#') continue;
			tmp = mask;
			tmp[id[tx][ty]] = 1;
			Q.push((node){nx, ny, tmp});
		}
	}
	return ans;
}
void solve() {
	int ans = 0;
	for(int i = 1; i <= 10; i ++)
		for(int j = 1; j <= 10; j ++) if (s[i][j] == 'W') {
			s[i][j] = '#';
			ans = max(ans, bfs(i, j));
			s[i][j] = 'W';
		}
	printf("%d\n", ans);
}

int main(){
	int T;
	scanf("%d", &T);
	for(int i = 1; i <= 10; i ++)
		for(int j = 1; j <= 10; j ++)
			col[i][j] = (i + j) & 1;
	for(int i = 1; i <= 10; i ++)
		for(int j = 1; j <= 10; j ++)
			if (col[i][j]) {
				id[i][j] = ++ tot;
				pos[tot] = make_pair(i, j);
			}
	while(T --) {
		init();
		solve();
	}
	return 0;
}
