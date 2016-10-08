#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;

struct upgrade {
	int type, who, base, id;
	void read() {
		scanf("%d%d%d", &type, &who, &base);
	}
};
int main(){
	scanf("%d%d%d", &k, &n, &m);
	for(int i = 1; i <= k; i ++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= n; i ++) {
		up[i].read();
		up[i].id = i;
	}
	return 0;
}
