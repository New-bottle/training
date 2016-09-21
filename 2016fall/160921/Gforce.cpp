#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 300010;

int n, m;
char s[N];
bool check() {
	int sum = 0;
	for(int i = 1; i <= n; i ++) {
		sum += s[i] == '(' ? 1 : -1;
		if (sum < 0) return 0;
	}
	return sum == 0;
}
void change(int pos) {
	s[pos] = (s[pos] == '(') ? ')' : '(';
}

int main(){
	while(scanf("%d%d", &n, &m) == 2) {
		scanf("%s", s + 1);
		for(int i = 1; i <= m; i ++) {
			int pos;
			scanf("%d", &pos);
			change(pos);
			for(int j = 1; j <= pos; j ++) {
				change(j);
				if (check()) {
					printf("%d\n", j);
					break;
				}
				change(j);
			}
		}
	}
	return 0;
}
