#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;
char s[N];
int times[30], a[N], k;
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d", &k);
	scanf("%s", s + 1);
	int l = 1, r = 1, ansl = 1, ansr = 1, n = strlen(s + 1);
	for(int i = 1; i <= n; i ++) a[i] = s[i] - 'a';
	times[a[1]] ++;
	int now = 1;
	while(l < n){
		while(now <= k && r < n){
			times[a[r + 1]] ++;
			if (times[a[r + 1]] == 1) now ++;
			if (now > k){
				times[a[r + 1]] --;
				now --;
				break;
			}else{
				r ++;
			}
		}
		if (ansr - ansl + 1 < r - l + 1){
			ansr = r;
			ansl = l;
		}
		times[a[l]] --;
		if (!times[a[l]]) now --;
		l ++;
		while (l > r){
			times[a[r + 1]] ++;
			if (times[a[r + 1]] == 1) now ++;
			r ++;
		}
	}
	printf("%d %d\n", ansl, ansr);
	return 0;
}
