#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;

int a[N], v[20];
int main(){
	int T, t;
	scanf("%d", &T);
	while(T --) {
		scanf("%d", &t); printf("%d ", t);
		for(int i = 1; i <= 12; i ++) scanf("%d", &a[i]);
		for(int i = 1; i <= 12; i ++) v[i] = a[i];
		sort(v + 1, v + 13);
		int num = unique(v + 1, v + 13) - v - 1;
		int ans = 0;
		for(int i = 1; i <= num; i ++) {
			int h = v[i];
			if (h == 0) continue;
			for(int l = 1; l <= 12; l ++)
				for(int r = l; r <= 12; r ++) {
					bool sign = 1;
					if (a[l - 1] >= h || a[r + 1] >= h) sign = 0;
					for(int i = l; i <= r; i ++) if (a[i] < h) sign = 0;
					ans += sign;
				}
		}
		printf("%d\n", ans);
	}
	return 0;
}
