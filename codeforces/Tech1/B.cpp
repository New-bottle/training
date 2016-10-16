#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100100;
typedef long long LL;

//double ans = 0.0;
int ans = 0;
char s[N];

int main(){
	gets(s);
	int l = (int)strlen(s), len = 0;
	s[l] = 'a';
	bool dot = 0;
	bool dec = 0;
	int tmp = 0;
	for(int i = 0; i <= l; i ++) {
		if (s[i] >= 'a' && s[i] <= 'z') {
			if (len == 2 && dot) {
				dec = 1;
			}
			if (dec) ans += tmp;
			else ans += tmp * 100;
			tmp = 0;
			dot = 0;
			len = 0;
		} else if (s[i] >= '0' && s[i] <= '9') {
			len ++;
			tmp = tmp * 10 + (s[i] - '0');
		} else if (s[i] == '.') {
			dot = 1;
			len = 0;
		}
	}
	int a = ans / 100;
	if (a / 1000000) {
		printf("%d.%03d.%03d", a / 1000000,
				(a - (a / 1000000) * 1000000) / 1000, a % 1000);
	} else if (a / 1000)
		printf("%d.%03d", a / 1000, a % 1000);
	else
		printf("%d", a);
	if (dec) {
		a = ans;
		a %= 100;
		printf(".%02d", a);
	}
	puts("");
	return 0;
}

