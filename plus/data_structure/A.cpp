#include<cstdio>
#include<queue>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 200010;
struct node {
	int v, x, y;
	bool operator < (const node &b) const {
		return v > b.v || (v == b.v && min(x, y) > min(b.x, b.y));
	}
};

int a[N], pre[N], suc[N], ans[N][2], n;
bool boy[N], out[N];
priority_queue<node>Q;
char s[N];

int main(){
	scanf("%d", &n);
	scanf("%s", s + 1);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= n; i ++) boy[i] = (s[i] == 'B');
	for(int i = 1; i <= n; i ++) pre[i] = i - 1, suc[i] = i + 1;
	for(int i = 1; i < n; i ++)
		if (boy[i] ^ boy[i + 1])
			Q.push((node){abs(a[i] - a[i + 1]), i, i + 1});
	int num = 0;
	while(!Q.empty()) {
		int x = Q.top().x, y = Q.top().y; Q.pop();
		if (out[x] || out[y]) continue;
		out[x] = out[y] = 1;
		num ++;
		ans[num][0] = x, ans[num][1] = y;
		if (x > y) swap(x, y);
		int i = pre[x], j = suc[y];
		pre[j] = i; suc[i] = j;
		if (i < 1 || j > n) continue;
		if (boy[i] ^ boy[j]) {
			Q.push((node){abs(a[i] - a[j]), i, j});
		}
	}
	printf("%d\n", num);
	for(int i = 1; i <= num; i ++) printf("%d %d\n", ans[i][0], ans[i][1]);
	return 0;
}
