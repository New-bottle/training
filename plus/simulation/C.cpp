#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 15;

struct Pai {
	int col, val;
}pai[6];
bool cmpc(const Pai &a, const Pai &b) {
	return a.col < b.col || (a.col == b.col && a.val < b.val);
}
bool cmpv(const Pai &a, const Pai &b) {
	return a.val < b.val || (a.val == b.val && a.col < b.col);
}
int getcol(char ch) {
	if (ch == 'S') return 0;
	if (ch == 'H') return 1;
	if (ch == 'D') return 2;
	if (ch == 'C') return 3;
}
int getval(char ch) {
	if (ch == 'A') return 1;
	if (ch == 'T') return 10;
	if (ch == 'J') return 11;
	if (ch == 'Q') return 12;
	if (ch == 'K') return 13;
	return ch - '0';
}

char s[4];

int num[15];
bool c[4];
void solve() {
	memset(num, 0, sizeof num);
	memset(c, 0, sizeof c);
	sort(pai + 1, pai + 6, cmpc);
	for(int i = 1; i < 6; i ++) num[pai[i].val] ++, c[pai[i].col] = 1;
	if (num[1]) num[14] = 1;
	int flush = 0;
	for(int i = 0; i < 4; i ++) flush += c[i]; //flush == 1 ? flush! : not_flush
	bool royal = 1;
	for(int i = 10; i <= 14; i ++) if (!num[i]) royal = 0;
	if (royal && flush == 1) {
		puts("royal flush");
		return;
	}
	bool straight = 0;
	for(int i = 1; i <= 10; i ++) {
		bool sign = 1;
		for(int j = i; j < i + 5; j ++) if (!num[j]) sign = 0;
		if (sign) {
			straight = 1;
			break;
		}
	}
	if (straight) {
		if (flush == 1) puts("straight flush");
		else puts("straight");
		return;
	}
	for(int i = 1; i <= 13; i ++)
		if (num[i] == 4) {
			puts("four of a kind");
			return;
		}
	int three = 0, two = 0;
	for(int i = 1; i <= 13; i ++) {
		if (num[i] == 3) three = 1;
		if (num[i] == 2) two ++;
	}
	if (three && two) {
		puts("full house");
		return;
	}

	if (flush == 1) {
		puts("flush");
		return;
	}
	if (three) {
		puts("three of a kind");
		return;
	}
	if (two == 2) {
		puts("two pairs");
		return;
	}
	if (two) {
		puts("pair");
		return;
	}
	puts("high card");
}

int main(){
	int T;
	scanf("%d", &T);
	while(T --) {
		for(int i = 1; i <= 5; i ++) {
			scanf("%s", s);
			pai[i].col = getcol(s[1]);
			pai[i].val = getval(s[0]);
		}
		solve();
	}
	return 0;
}
