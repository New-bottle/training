#include<cstdio>
#include<bitset>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 200010;

char s[N];
bool can[4];

int main(){
	scanf("%s", s + 1);
	int l = strlen(s + 1), c1 = 0, c0 = 0, cc = 0;
	if (l == 2) {
		if (s[1] == '0') {
			if (s[2] == '0') puts("00");
			else if (s[2] == '1') puts("01");
			else puts("00\n01");
		} else if (s[1] == '1') {
			if (s[2] == '0') puts("10");
			else if (s[2] == '1') puts("11");
			else puts("10\n11");
		} else {
			if (s[2] == '0') puts("00");
			else if (s[2] == '1') puts("01");
			else puts("00\n01");
			if (s[2] == '0') puts("10");
			else if (s[2] == '1') puts("11");
			else puts("10\n11");
		}
		return 0;
	}
	for(int i = 1; i <= l; i ++) {
		if (s[i] == '1') c1 ++;
		else if (s[i] == '0') c0 ++;
		else cc ++;
	}
	if (c1 + cc >= c0 + 2) can[3] = 1;
	if (c0 + cc >= c1 + 1) can[0] = 1;
	if (c1 <= l / 2 + (l & 1)  && c1 + cc >= l / 2 + (l & 1)) {
		if (s[l] == '1') can[1] = 1;
		else if (s[l] == '0') can[2] = 1;
	}
	if (c0 <= l / 2 && c0 + cc >= l / 2) {
		if (s[l] == '1') can[1] = 1;
		else if (s[l] == '0') can[2] = 1;
	}
	if (s[l] == '?') {
		if (c1 + 1 <= l / 2 + (l & 1) && c1 + cc >= l / 2 + (l & 1))
			can[1] = 1;
		if (c0 + 1 <= l / 2 && c0 + cc >= l / 2)
			can[2] = 1;
	}
	/*
	if (abs(c1 - c0) <= cc + 1) {
		if (s[l] == '1') can[1] = 1;
		else if (s[l] == '0') can[2] = 1;
		else can[1] = can[2] = 1;
	}
	*/
	for(int i = 0; i < 4; i ++) if (can[i])
		cout << bitset<2>(i) << endl;
	return 0;
}
