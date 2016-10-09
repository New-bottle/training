#include<cstdio>
#include<map>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 10000010;
typedef long long LL;

int n;

map<int, int> s;
int SG[N];
bool mark[10];
void getsg() {
	int n = 10000000;
	for(int i = 1; i <= n; i ++) {
		memset(mark, 0, sizeof mark);
		for(int j = 1; (LL)j * j <= i; j ++)
			if ((LL) j * j * j * j >= i && (LL)j * j <= i && j != i) mark[SG[j]] = 1;
		for(int j = 0; j <= n; j ++)
			if (!mark[j]) {
				SG[i] = j;
				break;
			}
	}
	for(int i = 1; i <= n; i ++) printf("%d\n", SG[i]);
	bool sign = 1;
	printf("sign = %d\n", sign);
}

int sg(LL x) {
	if (x <= 1000000) return (s.upper_bound((int)x) -> second) - 1;
	else {
		for(int i = 0; i < 10; i ++) mark[i] = 0;
		map<int,int>::iterator d, u;
		d = s.upper_bound((int)sqrt(sqrt(double(x))));
		u = s.upper_bound((int)sqrt(double(x)));
		u ++;
		for(auto i = d; i != u; i ++)
			mark[i -> second - 1] = 1;
		for(int i = 0; i < 10; i ++) if (!mark[i]) return i;
	}
}
int main(){
	s[4] = 1;
	s[16] = 2;
	s[82] = 3;
	s[6724] = 1;
	s[50626] = 4;
	s[1000001] = 2;
	/*
	s[4] = 2;
	s[16] = 3;
	s[256] = 4;
	s[65536] = 5;
	s[4294967296LL] = 6;
	s[9000000000000000LL] = 7;
	*/
//	getsg();
	scanf("%d", &n);
	int now = 0;
	for(int i = 1; i <= n; i ++) {
		LL x;
		cin >> x;
		now ^= sg(x);
	}
//	for(int i = 1; i <= 1000000; i ++) printf("%d\n", sg(i));
//	printf("%d\n", sg(777777777777LL));
	puts(now ? "Furlo" : "Rublo");
	return 0;
}
