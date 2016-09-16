#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

char s[100];
bool vis[26];

int main(){
	while(gets(s)) {
		memset(vis, 0, sizeof vis);
		int l = strlen(s);
		if (s[0] == 'E' && s[1] == 'N' && s[2] == 'D' && l == 3) break;
		bool yes = 1;
		for(int i = 0; i < l; i ++)
			if (s[i] != ' ') {
				if (vis[s[i] - 'A']) yes = 0;
				else vis[s[i] - 'A'] = 1;
			}
		if (yes) puts(s);
	}
	return 0;
}
