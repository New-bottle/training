#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1000010;
typedef long long LL;
LL a00, a01, a10, a11, n0, n1;
char s[N];

bool check() {
	if (a00 + a11 + a01 + a10 == 0) {
		s[0] = '0';
		return 1;
	}
	n0 = (LL)sqrt(a00 * 2) + 1;
	if ((LL)(n0 - 1) * n0 / 2 != a00) return 0;
	n1 = (LL)sqrt(a11 * 2) + 1;
	if ((LL)(n1 - 1) * n1 / 2 != a11) return 0;

//	printf("n0 = %d n1 = %d\n", n0, n1);
	if (!a00 && !a11) {
		if (a10 + a01 != 1) return 0;
		if (a10) s[0] = '1', s[1] = '0';
		else s[0] = '0', s[1] = '1';
		return 1;
	}
	if (!a01 && !a10) {
		if (!a00) n0 = 0;
		if (!a11) n1 = 0;
	}
	if ((a00 || a11) && a01 + a10 != n0 * n1) return 0;

	LL t10 = n0 * n1, t01 = 0, p0 = 0, p1 = 0;
	while(t01 + n1 <= a01 && n1) t01 += n1, p0 ++, t10 -= n1;

	LL now = 0, now1 = 0, now0 = 0;
	for(int i = 0; i < p0; i ++) s[now ++] = '0', now0 ++;
	p1 = n1 - (a01 - t01);
	for(int i = 0; i < p1; i ++) s[now ++] = '1', now1 ++;
	if (p1 < n1) {
		s[now ++] = '0'; now0 ++;
	}
	for(int i = 0; i < n1 - now1; i ++) s[now ++] = '1';
	for(int i = 0; i < n0 - now0; i ++) s[now ++] = '0';
	return 1;
}

int main(){
//	scanf("%d%d%d%d", &a00, &a01, &a10, &a11);
	while(cin >> a00 >> a01 >> a10 >> a11) {
		memset(s, 0, sizeof s);
		if (check()) {
			puts(s);
		} else puts("Impossible");
	}
	return 0;
}
