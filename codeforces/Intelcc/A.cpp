#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

char s[12], s2[12];

int getdata(char *s) {
	int now;
	if (s[0] == 'm') now = 1;
	else if (s[0] == 't' && s[1] == 'u') now = 2;
	else if (s[0] == 'w') now = 3;
	else if (s[0] == 't' && s[1] == 'h') now = 4;
	else if (s[0] == 'f') now = 5;
	else if (s[0] == 's' && s[1] == 'a') now = 6;
	else now = 0;
	return now;
}

int main() {
	scanf("%s", s);
	scanf("%s", s2);
	int now = getdata(s), nxt = getdata(s2);
//	printf("now = %d nxt = %d\n", now, nxt);
	if ((now + 28) % 7 == nxt || (now + 30) % 7 == nxt || (now + 31) % 7 == nxt)
		puts("YES");
	else puts("NO");
	return 0;
}
//28 30 31
