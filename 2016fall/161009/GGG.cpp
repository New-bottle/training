#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#define N 100001
using namespace std;

int data[N];
int n, m;

int belong[N];

struct node{
	int l, r;
	int id;
	friend bool operator < (const node &a, const node &b){
		return belong[a.l] == belong[b.l] ? a.r < b.r : belong[a.l] < belong[b.l];
	}
}q[N];

bool exist[N];
int ans = 0;

void Up(int x){
	ans ++;
	exist[data[x]] = 1;
	if(data[x] != n){
		if(exist[data[x] + 1]) ans --;
	}
	if(data[x] != 1){
		if(exist[data[x] - 1]) ans --;
	}
}

void Down(int x){
	ans --;
	exist[data[x]] = 0;
	if(data[x] != n){
		if(exist[data[x] + 1]) ans ++;
	}
	if(data[x] != 1){
		if(exist[data[x] - 1]) ans ++;
	}
}

int que[N];

void solve(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++){
		scanf("%d", &data[i]);
		exist[i] = 0;
	}
	
	int s = (int)sqrt(n);
	for(int i = 1; i <= n; i ++){
		belong[i] = (i - 1) / s + 1;
	}
	
	for(int i = 1; i <= m; i ++){
		scanf("%d%d", &q[i].l, &q[i].r);
		q[i].id = i;
	}
	sort(q + 1, q + m + 1);
	int L = 1, R = 0;
	ans = 0;
	for(int i = 1; i <= n; i ++){
		while(L > q[i].l) Up(-- L);
		while(R < q[i].r) Up(++ R);
		while(L < q[i].l) Down(L ++);
		while(R > q[i].r) Down(R --);
		que[q[i].id] = ans;
	}
	for(int i = 1; i <= m; i ++){
		printf("%d\n", que[i]);
	}
}

int main(){
	int testcase;
	scanf("%d", &testcase);
	for(int i = 1; i <= testcase; i ++){
		solve();
	}
	return 0;
}
