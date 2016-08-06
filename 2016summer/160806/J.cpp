#include<cstdio>
#include<queue>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const LL INF = 100000000000000000LL;
const int N = 1010, M = 2010;
int to[M << 1], nxt[M << 1], se[M << 1], l[M << 1], head[N], cnt;
void ins(int x, int y, int d, int s){
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt; l[cnt] = d; se[cnt] = s;
}
void add(int x, int y, int d, int s){
	ins(x, y, d, s); ins(y, x, d, s);
}

int n, m, T;
LL d[N];
queue<int>Q;
bool inq[N];
int check(int lv){
	for(int i = 1; i <= n; i ++) d[i] = INF;
	Q.push(1);
	d[1] = 0;
	inq[1] = 1;
	while(!Q.empty()){
		int x = Q.front(); Q.pop();
		inq[x] = 0;
		for(int i = head[x]; i; i = nxt[i]) if (se[i] <= lv)
			if (d[to[i]] > d[x] + l[i]){
				d[to[i]] = d[x] + l[i];
				if (!inq[to[i]]){
					Q.push(to[i]);
					inq[to[i]] = 1;
				}
			}
	}
	return d[n];
}

int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d%d", &n, &m);
	int l = 1, r = 0, mid, ans = 0, anst = 0, t;
	for(int i = 1; i <= m; i ++){
		static int x, y, d, s;
		scanf("%d%d%d%d", &x, &y, &d, &s);
		add(x, y, d, s);
		r = max(r, s);
	}
	scanf("%d", &T);
	while(l <= r){
		mid = (l + r) >> 1;
		t = check(mid);
		if (t <= T) ans = mid, anst = t, r = mid - 1;
		else l = mid + 1;
	}
	if (ans) {
		puts("YES");
		printf("%d %d\n", ans, anst);
	}else{
		puts("NO");
	}
	return 0;
}
