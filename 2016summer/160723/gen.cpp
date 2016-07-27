#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
using namespace std;

int pos[16][16];
int main(){
	freopen("B.in","w",stdout);
	srand(time(0));
	int n = 15, m = 15, lim = 14, zhangai = 100;
	int numy = rand() % lim, numg = lim - numy;
	for(int i = 1; i <= numy; i ++){
		int x = rand() % n + 1, y = rand() % n + 1;
		if (pos[x][y]){
			i --;
			continue;
		}
		pos[x][y] = 1;
	}
	for(int i = 1; i <= numg; i ++){
		int x = rand() % n + 1, y = rand() % n + 1;
		if (pos[x][y]){
			i --;
			continue;
		}
		pos[x][y] = 2;
	}
	for(int i = 1; i <= zhangai; i ++){
		int x = rand() % n + 1, y = rand() % n + 1;
		if (pos[x][y]){
			i --;
			continue;
		}
		pos[x][y] = 3;
	}
	printf("%d %d\n",n,m);
	bool yes = 0;
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= m; j ++){
			if (pos[i][j] == 0 && yes) printf("S");
			if (pos[i][j] == 0 && !yes){
				printf("F");
				yes = 1;
			}
			if (pos[i][j] == 1) printf("Y");
			if (pos[i][j] == 2) printf("G");
			if (pos[i][j] == 3) printf("D");
		}
		puts("");
	}
	puts("0 0");
	return 0;
}
