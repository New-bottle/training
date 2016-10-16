#include<cstdio>
#include<vector>
#include<map>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1000010;
map<int,int>c[N];
vector<int>s[N];
int n, m, tot = 1, belong[N];

void Ins(const vector<int> &s, int rk) {
	int l = s.size(), x = 1;
	for(int i = 0; i < l; i ++) {
		if (!c[x][s[i]]) c[x][s[i]] = ++tot;
		x = c[x][s[i]];
	}
	sign[x] = 1;
}

int main() {
	scanf("%d%d", &n, &m);
	bool sign = 1;
	for(int i = 1; i <= n; i ++) {
		int len;
		scanf("%d", &len);
		for(int j = 1; j <= len; j ++) {
			int x;
			scanf("%d", &x);
			s[j].push_back(x);
		}
		if (!Ins(j, i)) sign = 0;
	}
	
	return 0;
}
