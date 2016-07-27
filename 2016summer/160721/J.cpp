#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include <bitset>
using namespace std;

const int N = (1 << 20) + 1;

typedef long long LL;
char s[100];
int mx[N], mn[N], n, num[N];
LL f[N];

void pre(){
	for(int mask = 0; mask < (1 << 20); mask ++){
		mx[mask] = -1; mn[mask] = 100; num[mask] = 0;
		for(int i = 0; i < 20; i ++)
			if (mask >> i & 1){
				mn[mask] = min(mn[mask], i + 1);
				mx[mask] = max(mx[mask], i + 1);
				num[mask] ++;
			}
	}
}

int last[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	pre();
	while(cin >> (s + 1)){
		n = strlen(s + 1);
		for(int i = 1; i < (1 << n); i ++) f[i] = 0;
		f[0] = 1;
		int tmp, i, j;
		for(int mask = 0; mask < (1 << n); mask ++) if (f[mask]){
			i = num[mask];
			if (s[i + 1] == '+'){
				tmp = (~mask) & ((1 << n) - 1);
				while((j = mx[tmp]) && j > i + 1){
					tmp ^= 1 << (j - 1);
					f[mask ^ (1 << (j - 1))] += f[mask];
				}
			}else{
				tmp = (~mask) & ((1 << n) - 1);
				while((j = mn[tmp]) && j < i + 1){
					tmp ^= 1 << (j - 1);
					f[mask ^ (1 << (j - 1))] += f[mask];
				}
			}
		}
		cout << f[(1 << n) - 1] << endl;
	}
	return 0;
}
