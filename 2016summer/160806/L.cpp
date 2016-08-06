#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int N = 100010;
struct event{
	int pos, rank;
}q[N << 1];
bool operator < (const event& a, const event &b){
	return a.pos < b.pos || (a.pos == b.pos && a.rank < b.rank);
}
int l[N], r[N], n;

int main(){
//	freopen("input.txt","r",stdin);
//	freopen("output.txt","w",stdout);
	scanf("%d", &n);
	LL now = 0, ans = 0, pos = 0, num = 0, p;
	for(int i = 1; i <= n; i ++){
		scanf("%d%d", &l[i], &r[i]);
		q[i] = (event){l[i], 1};
		q[n + i] = (event){r[i], 2};
		now += l[i];
	}
	sort(q + 1, q + n * 2 + 1);
	for(int i = 1; i <= n * 2; i ++){
		if (q[i].rank == 1){
			now -= q[i].pos;
			num ++;
		} else {
			p = q[i].pos;
			if (ans < p * num + now) {
				ans = p * num + now;
				pos = p;
			}
			num --;
		}
	}
	printf("%lld %lld\n", pos, ans);
	return 0;
}
