#include<cstdio>
#include<queue>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int INF = 1e9;
const int N = 100010;
vector<int>even;
typedef pair<int,int> pii;
pii have[N];
int a[10], b[N], n;
char s[20];

inline int id(char *s) {
	if (s[0] == 'S') return 1;
	if (s[0] == 'M') return 2;
	if (s[0] == 'L') return 3;
	if (s[1] == 'L') return 4;
	if (s[2] == 'L') return 5;
	if (s[3] == 'L') return 6;
}

bool judge() {
	for(int i = 1; i <= 6; i ++) {
		if (a[i] < 0) return 0;
	}
	for(int j = 6; j; j --) {
		for(int i = 0; i < even.size(); i ++) {
			int x = even[i];
			if (b[x]) continue;
			if (have[x].first == j) {
				if (a[j] > 0) {
					a[j] --;
					b[x] = j;
				} else return 0;
			}
		}
		for(int i = 0; i < even.size(); i ++) {
			int x = even[i];
			if (b[x]) continue;
			if (have[x].second == j) {
				if (a[j] > 0) {
					a[j] --;
					b[x] = j;
				}
			}
		}
	}
	return 1;
}

int main(){
	for(int i = 1; i <= 6; i ++) scanf("%d", &a[i]);
	scanf("%d" ,&n);
	for(int i = 1; i <= n; i ++) {
		scanf("%s", s);
		int l = strlen(s), pos = l;
		for(int j = 0; j < l; j ++) if (s[j] == ',') pos = j;
		if (pos == l) {
			b[i] = id(s);
			a[id(s)] --;
		} else {
			int x = id(s), y = id(s + pos + 1);
			even.push_back(i);
			if (x > y) swap(x, y);
			have[i] = make_pair(x, y);
		}
	}
	if (!judge()) {
		puts("NO");
	} else {
		puts("YES");
		for(int i = 1; i <= n; i ++) {
			if (b[i] == 1) puts("S");
			if (b[i] == 2) puts("M");
			if (b[i] == 3) puts("L");
			if (b[i] == 4) puts("XL");
			if (b[i] == 5) puts("XXL");
			if (b[i] == 6) puts("XXXL");
		}
	}
	return 0;
}
