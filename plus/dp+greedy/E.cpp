#include<cstdio>
#include<queue>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
#define debug

const int N = 100010;

struct node {
	int l, r, c, id;
	bool operator < (const node &b) const {
		return r > b.r;
	}
}a[N];
int n, m;

vector<int>have[N];

int ans[N];
int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i ++) {
		scanf("%d%d", &a[i].r, &a[i].c);
		a[i].l = n - a[i].c + 1;
		a[i].id = i;
		have[a[i].l].push_back(i);
	}
	int num = 0;
	priority_queue<node>Q;
	for(int i = 1; i <= n; i ++) {
		for(int j = 0; j < have[i].size(); j ++)
			Q.push(a[have[i][j]]);
		while(!Q.empty() && Q.top().r < i) Q.pop();
		if (!Q.empty()) {
			num ++;
			ans[num] = Q.top().id;
			Q.pop();
		}
	}
	printf("%d\n", num);
	for(int i = 1; i <= num; i ++) 
		printf("%d%c", ans[i], i == num ? '\n' : ' ');
	return 0;
}
