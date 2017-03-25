#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 500010;

char s[N], st[N];
vector<int> wen;
bool del[N];
int n, where[N];
int top = 0;

bool judge()
{
	for (int i = 1; i <= n; ++i)
		if (s[i] == ')') {
	//		if (!top) return 0;
			if (st[top] == '(') {
				del[where[top]] = 1;
				del[i] = 1;
				--top;
			} else {
				st[++top] = ')';
				where[top] = i;
			}
		} else if (s[i] == '(') {
			st[++top] = '(';
			where[top] = i;
		} else {
			wen.push_back(i);
//			st[++top] = '?';
		}
	top = 0;
	for (int i = 1; i <= n; ++i)
		if (!del[i]) st[++top] = s[i];
//	for (int i = 1; i <= top; ++i) printf("%c", st[i]); puts("");
	int cl = 0, cr = 0, cw = 0;
	for (int i = 1; i <= top; ++i) {
		if (st[i] == '?') ++cw;
		else if (st[i] == '(') ++cl;
		else ++cr;
		if (cr > cw) return 0;
	}
	if ((cw - cr - cl) & 1) return 0;
	for (int i = 0; i < cr + (cw - cr - cl) / 2; ++i)
		s[wen[i]] = '(';
	for (int i = 0; i < cw; ++i) if (s[wen[i]] == '?') s[wen[i]] = ')';
	int num = 0;
	for (int i = 1; i <= n; ++i) {
		if (s[i] == '(') ++num;
		else if (num) --num;
		else return 0;
	}
	return num == 0;
}
int main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	if (!judge()) {
		puts("Impossible");
		return 0;
	}
	puts(s + 1);
	return 0;
}
/*
	int c1 = 0, c2 = 0, i;
	for (i = 1; i <= top; ++i)
		if (st[i] == '?') ++c1;
		else break;
	for (;i <= top; ++i)
		if (st[i] == ')') ++c2;
		else break;
	if (c1 < c2) return 0;
	int delta = c1 - c2, where = c1;
	for (int i = 0; i < (c1 - c2) / 2; ++i)
		s[wen[i << 1 | 1]] = ')';
	for (int i = 0; i < c1; ++i)
		if (s[wen[i]] == '?') s[wen[i]] = '(';

	c1 = delta & 1; c2 = 0;
//	printf("c1 = %d c2 = %d\n", c1, c2);
	for (; i <= top; ++i)
		if (st[i] == '(') ++c1;
		else break;
	for (; i <= top; ++i)
		if (st[i] == '?') ++c2;
//	printf("c1 = %d c2 = %d\n", c1, c2);
	if (c2 < c1) return 0;
	if ((c2 - c1) & 1) return 0;
	int cnt = 0;
	for (int i = where; i < where + c2; ++i)
		if (cnt < (c2 - c1) >> 1) {
			s[wen[i]] = '(';
			++cnt;
		} else s[wen[i]] = ')';
	return 1;
	*/
