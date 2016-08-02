#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;
char s[N], t[N];
int nxt[N];

void kmp(){
	memset(t, 0, sizeof t);
	memset(nxt, 0, sizeof nxt);
	int n = strlen(s + 1), m = 0, last = 1, j = 1;
	t[++ m] = s[1];
	for(int i = 2; i <= n; i ++){
		while(j && s[i] != t[j + 1]) j = nxt[j];
		if (s[i] == t[j + 1]){
			j ++;
			if (j == m && i != n){
				last = i;
				j = nxt[j];
			}
		}else if (i != n){
			for(int k = last + 1; k <= i; k ++){
				t[++ m] = s[k];
				int j = nxt[m - 1];
				while(j && t[j + 1] != t[m]) j = nxt[j];
				nxt[m] = t[j + 1] == t[m] ? j + 1 : 0;
			}
			j = m;
			last = i;
		}
	}
	if (j != m){
		for(int k = last + 1; k <= n; k ++) t[++ m] = s[k];
	}
	printf("%d\n", m);
}
int main(){
	int cs = 0;
	while(scanf("%s", s + 1) == 1){
		printf("Case %d: ", ++ cs);
		kmp();
	}
	return 0;
}
