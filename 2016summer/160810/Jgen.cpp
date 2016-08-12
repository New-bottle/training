#include<cstdio>
#include<ctime>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

bool vis[100010];
char s1[100010], s2[100010], s3[100010];


void make(){
	memset(vis, 0, sizeof vis);
	memset(s1, 0, sizeof s1);
	memset(s2, 0, sizeof s2);
	memset(s3, 0, sizeof s3);
	int n = 7, m = rand() % n;
	printf("%d %d\n", n, m);
	int same = rand() % n, both = rand() % n;
//	int same = 7000, both = 10000;
	
	for(int i = 1; i <= n; i ++){
		s1[i] = rand()%26 + ((rand()&1) ? 'a' : 'A');
		s2[i] = rand()%26 + ((rand()&1) ? 'a' : 'A');
		s3[i] = rand()%26 + ((rand()&1) ? 'a' : 'A');
	}
	for(int i = 1; i <= both; i ++){
//		int x = rand() % n + 1;
		int x = i;
		if (vis[x]) {
			i --;
			continue;
		}
//		vis[x] = 1;
		int y = rand()%3 + 1;
		if (y == 1){
			s3[x] = s2[x];
		}else if (y == 2){
			s3[x] = s1[x];
		}else{
			s2[x] = s1[x];
		}
	}
	for(int i = 1; i <= same; i ++){
		int x = rand() % n + 1;
		if (vis[x]){
			i --;
			continue;
		}
		s2[x] = s3[x] = s1[x];
		vis[x] = 1;
	}
	puts(s1 + 1);
	puts(s2 + 1);
	puts(s3 + 1);
}

int main(){
	freopen("J.in","w",stdout);
	srand(time(0));
	int T = 1;
	while(T --){
		make();
	}
	puts("0 0");
	return 0;
}
