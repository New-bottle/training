#include<cstdio>
#include<bitset>
#include<queue>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int fx[] = {1,-1,0,0},
	  	  fy[] = {0,0,1,-1};
const int N = 17;

int n, m, num, tot, st;
char c[N][N];
bool sign[N][N];
struct node{
	int x, y;
}p[20];
int d[N][N], dis[N][N];

queue<node>Q;
void bfs(int k){
	while(!Q.empty()) Q.pop();
	memset(d, -1, sizeof d);
	Q.push((node){p[k].x, p[k].y});
	d[p[k].x][p[k].y] = 0;
	int x, y, tx, ty;
	while(!Q.empty()){
		x = Q.front().x, y = Q.front().y; Q.pop();
		for(int i = 0; i < 4; i ++){
			tx = x + fx[i], ty = y + fy[i];
			if (tx < 1 || ty < 1 || tx > n || ty > m || !sign[tx][ty] || d[tx][ty] != -1) continue;
			d[tx][ty] = d[x][y] + 1;
			Q.push((node){tx, ty});
		}
	}
	for(int i = 0; i < num; i ++)
		dis[k][i] = d[p[i].x][p[i].y];
}
void build(){
	num = tot = 0;
	memset(p, 0, sizeof p);
	memset(sign, 0, sizeof sign);
	memset(dis, 0, sizeof dis);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++){
			if (c[i][j] == 'F'){
				st = num;
				p[num] = (node){i, j};
				num ++;
				sign[i][j] = 1;
			}else if (c[i][j] == 'Y'){
				tot |= 1 << num;
				p[num] = (node){i, j};
				num ++;
				sign[i][j] = 1;
			}else if (c[i][j] == 'G'){
				p[num] = (node){i, j};
				num ++;
				sign[i][j] = 1;
			}else if (c[i][j] == 'S') sign[i][j] = 1;
			else if (c[i][j] == 'D') sign[i][j] = 0;
		}
	for(int i = 0; i < num; i ++) bfs(i);
}

int g[1 << N][N];
bool vis[1 << N][N];
bool jud(int len){
	while(!Q.empty()) Q.pop();
	memset(g, -1, sizeof g);
	memset(vis, 0, sizeof vis);
	Q.push((node){1 << st, st});
	g[1 << st][st] = len;
	vis[1 << st][st] = 1;
	while(!Q.empty()){
		int mask = Q.front().x, pos = Q.front().y, nxt, tmp;
		Q.pop();
		vis[mask][pos] = 0;
		if ((mask & tot) == tot) return 1;
		for(int i = 0; i < num; i ++){
			if ((1 << i) & mask) continue;
			if (dis[pos][i] == -1) continue;
			if (dis[pos][i] > g[mask][pos]) continue;
			nxt = mask | (1 << i);
			if (!(tot >> i & 1)) tmp = len;
			else tmp = g[mask][pos] - dis[pos][i];
			if (g[nxt][i] < tmp){
				g[nxt][i] = tmp;
				if (!vis[nxt][i]){
					Q.push((node){nxt, i});
					vis[nxt][i] = 1;
				}
			}
		}
	}
	return 0;
}
void work(){
	for(int i = 0; i < num; i ++)
		if (dis[st][i] == -1 && (tot >> i & 1)){
			puts("-1");
			return;
		}
	int l = 0, r = n * m * 20, mid, ans = -1;
	while(l <= r){
		mid = (l + r) >> 1;
		if (jud(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	printf("%d\n",ans);
}
int main(){
	while(scanf("%d%d", &n, &m) == 2 && n && m){
		for(int i = 1; i <= n; i ++) scanf("%s", c[i] + 1);
		build();
		work();
	}
	return 0;
}
