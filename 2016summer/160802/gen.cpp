#include<cstdio>
#include<cmath>
#include<map>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

map<int,bool>mp[100010];
void work1(){
	int n = 100000, m = 100000;
	printf("%d %d\n", n, m);
	for(int i = 1; i <= n; i ++) printf("%d ", rand() & 1); puts("");
	for(int i = 1; i < m; i ++) printf("%d %d %d\n", 1, i + 1, rand());
	printf("%d %d %d\n", 99999, 100000, rand());
	int q = 100000;
	printf("%d\n", q);
	for(int i = 1; i <= q; i ++){
		if (rand() & 1){
			printf("Asksum %d %d\n", rand() & 1, rand() & 1);
		}else{
			printf("Change %d\n", 1);
		}
	}
}
void work2(){
	int n = 100000, m = 100000;
	printf("%d %d\n", n, m);
	for(int i = 1; i <= n; i ++) printf("%d ", rand() & 1); puts("");
	for(int i = 1; i <= 50000; i ++) printf("%d %d %d\n", 1, i + 1, rand());
	for(int i = 1; i <= 50000; i ++) printf("%d %d %d\n", 2, i + 50001, rand());
	int q = 100000;
	printf("%d\n", q);
	for(int i = 1; i <= q; i ++){
		if (rand() & 1){
			printf("Asksum %d %d\n", rand() & 1, rand() & 1);
		}else{
			printf("Change %d\n", 1);
		}
	}
}
void work3(){
	int n = 100000, m = 100000;
	printf("%d %d\n", n, m);
	for(int i = 1; i <= n; i ++) printf("%d ", rand() & 1); puts("");
	for(int i = 1; i <= m; i ++) printf("%d %d %d\n", 1, 2, rand()); 
	int q = 100000;
	printf("%d\n", q);
	for(int i = 1; i <= q; i ++){
		if (rand() & 1){
			printf("Asksum %d %d\n", rand() & 1, rand() & 1);
		}else{
			printf("Change %d\n", (rand()&1) + 1);
		}
	}
}

int main(){
	freopen("D.in","w",stdout);
	int T = 10;
	srand(time(0));
	work1();
	work2();
	work3();
	while(T --){
		int n = 100000, m = 100000;
		printf("%d %d\n", n, m);
		for(int i = 1; i <= n; i ++) printf("%d ", rand()&1); puts("");
		int x, y;
//		for(int i = 1; i <= m; i ++) printf("%d %d %d\n", 1, 2, rand());
		int times = 0, now = 1;
		for(int i = 1; i <= m; i ++){
			x = now; y = rand() % n + 1;
			if (x == y){
				i --;
				continue;
			}
//			while(mp[x][y]){
//				x = rand() % n + 1; y = rand() % n + 1;
//			}
//			mp[x][y] = mp[y][x] = 1;
			printf("%d %d %d\n", x, y, rand());
			times ++;
			if (times >= sqrt(n)){
				times = 0;
				now ++;
			}
		}
		int q = 100000;
		printf("%d\n", q);
		for(int i = 1; i <= q; i ++){
			if (rand() & 1){
				printf("Asksum %d %d\n", rand() & 1, rand() & 1);
			}else{
				printf("Change %d\n", rand()%n);
			}
		}
	}
	return 0;
}
