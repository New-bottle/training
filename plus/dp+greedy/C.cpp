#include<cstdio>
#include<bitset>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 600010;
const int dx[] = {1, 1, 0},
	  	  dy[] = {0, 1, 1};

int v, id[10][10];
vector<int>moves;
void getmoves() {
	int cnt = -1;
	memset(id, -1, sizeof id);
	for(int i = 1; i <= 3; i ++) id[1][i] = ++cnt;
	for(int i = 1; i <= 4; i ++) id[2][i] = ++cnt;
	for(int i = 1; i <= 5; i ++) id[3][i] = ++cnt;
	for(int i = 2; i <= 5; i ++) id[4][i] = ++cnt;
	for(int i = 3; i <= 5; i ++) id[5][i] = ++cnt;

	for(int i = 1; i <= 5; i ++)
		for(int j = 1; j <= 5; j ++) if (id[i][j] != -1) {
			int tmp = (1 << id[i][j]);
			moves.push_back(tmp);
			for(int k = 0; k < 3; k ++) {
//				printf("(%d, %d) -> ", i, j);
				int tx = i, ty = j;
				tmp = (1 << id[i][j]);
				for(int t = 1; t <= 4; t ++) {
					tx += dx[k]; ty += dy[k];
					if (id[tx][ty] == -1) break;
//					printf("(%d, %d) -> ", tx, ty);
					tmp |= (1 << id[tx][ty]);
//					printf("__%d__", tmp);
					moves.push_back(tmp);
				}
//				printf("%d\n", tmp);
			}
		}
//	for(int i = 0; i < moves.size(); i ++) printf("%d\n", moves[i]);
//	printf("%d\n", moves.size());
}

int vis[N];
bool dfs(int mask) {
//	printf("dfs %d\n", mask);
	if (mask == 0) return 0;
	if (vis[mask] != -1) return vis[mask];
	for(int i = 0; i < (int)moves.size(); i ++)
		if ((mask & moves[i]) == moves[i]) dfs(mask ^ moves[i]);
	for(int i = 0; i < (int)moves.size(); i ++)
		if ((mask & moves[i]) == moves[i])
			if (dfs(mask ^ moves[i]) == 0) return (vis[mask] = 1);
	return (vis[mask] = 0);
}

char s[10];
int main(){
	memset(vis, -1, sizeof vis);
	for(int i = 0; i < 19; i ++) {
		scanf("%s", s);
		if (s[0] != '.') v |= (1 << i);
//		puts(s);
	}
//	printf("v = "); cout << bitset<19>(v) << endl;
//	cout << "v = " << v << endl;
	getmoves();
	if (dfs(v)) puts("Karlsson");
	else puts("Lillebror");
//	for(int i = 1; i < (1 << 19); i ++) 
//		if (vis[i] != -1) printf("vis[%d] = %d\n", i, vis[i]);
	return 0;
}
