#include<cstdio>
#include<map>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1100;
int a, b;
int now[N], ans;
int main(){
	scanf("%d%d", &a, &b);

	ans = 0;
	now[++ans] = b;
	while(b > a) {
		if ((b & 1) == 0) b >>= 1;
		else if (b % 10 == 1) b = b / 10;
		else {
			puts("NO");
			return 0;
		}
		now[++ans] = b;
	}
	if (now[ans] != a) {
		puts("NO");
		return 0;
	}
	puts("YES");
	printf("%d\n", ans);
	for(int i = ans; i; i --)
		printf("%d%c", now[i], i == 1 ? '\n' : ' ');
	return 0;
}
