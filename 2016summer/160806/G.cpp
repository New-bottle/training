#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 200010;
struct node{
	int v, id;
}a[2010];
bool operator < (const node &a, const node &b){
	return a.v < b.v;
}
int k, n, num[2010];
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d%d", &k, &n);
	for(int i = 1; i <= n; i ++){
		scanf("%d", &a[i].v);
		a[i].id = i;
	}
	sort(a + 1, a + n + 1);
	int now = 0;
	for(int i = 1; i <= n; i ++){
		now = min(k, a[i].v);
		num[a[i].id] += now;
		k -= now;
		if (k == 0) break;
	}
	for(int i = 1; i <= n; i ++) printf("%d ", num[i]); puts("");
	return 0;
}
