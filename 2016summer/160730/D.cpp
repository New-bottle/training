#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int dx[] = {1, 0, -1, 0},
	  	  dy[] = {0, 1, 0, -1};
const int N = 910;

int a[N][N], n, m, mp[32][32], id[32][32];
//inv[1] = 1
//inv[2] = 2
inline int inv(int x){return x;}
void gauss(int n){
	for(int i = 1; i <= n; i ++){
		int r = i;
		for(int j = i; j <= n; j ++) if (a[j][i]){
			r = j;
			break;
		}
		if (r != i) for(int j = 1; j <= n + 1; j ++) swap(a[i][j], a[r][j]);
		if (a[i][i] == 0) continue;
		for(int j = 1; j <= n; j ++) if (i != j)
			for(int k = n + 1; k >= i; k --)
				if (a[j][i] && a[i][k]) a[j][k] = (a[j][k] - a[j][i] * inv(a[i][i]) * a[i][k] % 3 + 3) % 3;
	}
}
void init(){
	scanf("%d%d", &n, &m);
	int tot = 0;
	memset(a, 0, sizeof a);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++){
			scanf("%d", &mp[i][j]);
			id[i][j] = ++ tot;
		}
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++){
			a[id[i][j]][id[i][j]] = 2;
			//a[id[i][j]][tot + 1] = mp[i][j];
			a[id[i][j]][tot + 1] = (3 - mp[i][j]) % 3;
			for(int k = 0; k < 4; k ++){
				int x = i + dx[k], y = j + dy[k];
				if (x < 1 || x > n || y < 1 || y > m) continue;
				a[id[i][j]][id[x][y]] = 1;
			}
		}
	gauss(tot);
	int ans = 0;
	for(int i = 1; i <= tot; i ++)
		ans += a[i][i] * a[i][tot + 1] % 3;
	printf("%d\n", ans);
	for(int i = 1; i <= tot; i ++)
		for(int j = 1; j <= a[i][i] * a[i][tot + 1] % 3; j ++) printf("%d %d\n", (i - 1) / m + 1, (i - 1) % m + 1);
}
int main(){
	int T;
	scanf("%d", &T);
	while(T --){
		init();
	}
	return 0;
}
