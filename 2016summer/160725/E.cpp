#include<cstdio>
#include<queue>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
//D L R U
const int dx[] = {1, 0, 0, -1},
	      dy[] = {0, -1, 1, 0};
const int N = 100;

int a[N][N], b[N][N], way[N][N], stx1, stx2, sty1, sty2, edx1, edx2, edy1, edy2;
typedef pair<int, int> pii;
pii from[N][N];
bool vis[N][N];

inline char get(int x){
	if (x == 0) return 'D';
	if (x == 1) return 'L';
	if (x == 2) return 'R';
	if (x == 3) return 'U';
	return '!';
}
inline bool bar(int a[N][N], int x, int y, int dir){
	if (dir == 0) return a[x][y] >> 1 & 1;
	if (dir == 1) return a[x][y] & 1;
	return a[x][y] >> dir & 1;
}
inline bool can(int a[N][N], int x, int y){
	return a[x][y] >> 4;
}

queue<pii >Q;
int where;
void bfs(int pos1, int pos2){
	while(!Q.empty()) Q.pop();
	memset(vis, 0, sizeof vis);
	memset(from, 0, sizeof from);
	memset(way, 0, sizeof way);

	Q.push(make_pair(pos1, pos2));
	from[pos1][pos2] = make_pair(0,0);
	vis[pos1][pos2] = 1;
	where = 0;
	while(!Q.empty()){
		int x1 = Q.front().first / 10, y1 = Q.front().first % 10,
			x2 = Q.front().second / 10, y2 = Q.front().second % 10;
//		printf("(%d, %d) (%d, %d)  ", x1, y1, x2, y2);
		where ++;
//		printf("%d\n", where);
		for(int i = 0; i < 4; i ++){
			int tx1 = x1 + dx[i], ty1 = y1 + dy[i],
				tx2 = x2 + dx[i], ty2 = y2 + dy[i], t1, t2;
			if (bar(a, x1, y1, i))
				tx1 = x1, ty1 = y1;
			else tx1 = x1 + dx[i], ty1 = y1 + dy[i];
			if (can(a, tx1, ty1) == 0) continue;

			if (bar(b, x2, y2, i))
				tx2 = x2, ty2 = y2;
			else tx2 = x2 + dx[i], ty2 = y2 + dy[i];
			if (can(b, tx2, ty2) == 0) continue;

			t1 = tx1 * 10 + ty1; t2 = tx2 * 10 + ty2;
			if (vis[t1][t2]) continue;
			Q.push(make_pair(t1,t2));
			from[t1][t2] = Q.front();
			vis[t1][t2] = 1;
			way[t1][t2] = i;
			if (t1 == edx1 * 10 + edy1 && t2 == edx2 * 10 + edy2) return;
		}
		Q.pop();
	}
}

char ans[2000000];
void getans(){
	int t1 = edx1 * 10 + edy1, t2 = edx2 * 10 + edy2, cnt = 0, n1, n2;
	if (vis[t1][t2] == 0){
		puts("-1");
		return;
	}
	while(from[t1][t2].first){
		ans[++ cnt] = get(way[t1][t2]);
		n1 = from[t1][t2].first;
		n2 = from[t1][t2].second;
		t1 = n1; t2 = n2;
		if (t1 == 0) break;
	}
	for(int i = cnt; i; i --) printf("%c", ans[i]); puts("");
}

int main(){
	int T;
	scanf("%d", &T);
	T --;
	for(int i = 1; i <= 6; i ++)
		for(int j = 1; j <= 6; j ++){
			scanf("%d", &b[i][j]);
			if (b[i][j] >> 5 & 1) stx2 = i, sty2 = j;
			if (b[i][j] >> 6 & 1) edx2 = i, edy2 = j;
		}
	while(T --){
		swap(a, b);
		swap(stx1, stx2); swap(sty1, sty2);
		swap(edx1, edx2); swap(edy1, edy2);
		for(int i = 1; i <= 6; i ++)
			for(int j = 1; j <= 6; j ++){
				scanf("%d", &b[i][j]);
				if (b[i][j] >> 5 & 1) stx2 = i, sty2 = j;
				if (b[i][j] >> 6 & 1) edx2 = i, edy2 = j;
			}
		bfs(stx1 * 10 + sty1, stx2 * 10 + sty2);
		getans();
	}
	return 0;
}
