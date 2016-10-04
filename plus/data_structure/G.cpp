#include<cstdio>
#include<set>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;

int n;
struct node{
	int h, l, r;
}a[N];
struct Event {
	int x, y, rank;
	bool operator < (const Event &b) const {
		return x < b.x || (x == b.x && rank > b.rank);
		//insert-check-delete-check
	}
}e[N << 1];

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)
		scanf("%d%d%d", &a[i].h, &a[i].l, &a[i].r);
	int tot = 0;
	for(int i = 1; i <= n; i ++) {
		e[++ tot] = (Event){a[i].l, a[i].h, 1};
		e[++ tot] = (Event){a[i].r, a[i].h, 0};
	}
	
	sort(
	return 0;
}
