#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 50;

int n, m, a[N][N];
vector<int> pos[N];

bool check() {
	for(int i = 1; i <= n; i ++) {
		int num = 0;
		for(int j = 1; j <= m; j ++)
			if (a[i][j] != j) num ++;
		if (num > 2) return false;
	}
	return true;
}
bool solve() {
	if (check()) return true;
	for(int i = 1; i <= m; i ++)
		for(int j = i + 1; j <= m; j ++) {
			for(int k = 1; k <= n; k ++) swap(a[k][i], a[k][j]);
			if (check()) return true;
			for(int k = 1; k <= n; k ++) swap(a[k][i], a[k][j]);
		}
	return false;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			scanf("%d", &a[i][j]);
	
	if (solve()) puts("YES");
	else puts("NO");
	return 0;
}
