#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<map>
using namespace std;

map<int, bool>mp[200010];
const int M = 1e9;
int main(){
	freopen("F.in","w",stdout);
	srand(time(0));
	int n = 200000, m = 200000;
	int T = 3;
	printf("%d\n",T);
	for(int i = 1; i <= T; i ++){
		printf("%d %d\n", n, m);
		for(int i = 1; i <= n; i ++) mp[i].clear();
		for(int i = 1; i <= n; i ++)
			printf("%d ", rand() % M + 1);
		puts("");
		int x, y;
		for(int i = 1; i <= m; i ++){
			x = rand() % n + 1, y = rand() % n + 1;
			if (x == y){
				i--;
				continue;
			}
			if (mp[x].find(y)!=mp[x].end()) continue;
			mp[x][y] = 1;
			mp[y][x] = 1;
			printf("%d %d\n",x, y);
		}
	}
	return 0;
}
