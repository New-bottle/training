#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

#define maxn (100010)
int a[maxn];

int main()
{
	freopen("G.in","w",stdout);
	int N = 100000,Q = 100000;
	for (int i = 1;i <= N;++i) a[i] = i;
	random_shuffle(a+1,a+N+1);
	printf("%d %d\n",N,Q);
	for (int i = 1;i <= N;++i) printf("%d ",a[i]);
	puts("");
	for (int i = 1;i <= Q;++i)
	{
		int l = rand()%N+1,r = rand()%N+1;
		if (l > r) swap(l,r);
		printf("%d %d\n",l,r);
	}
	fclose(stdout); fclose(stdout);
	return 0;
}
