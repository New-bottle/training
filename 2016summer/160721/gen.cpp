#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<ctime>
using namespace std;

const int N = 4;
int main(){
	freopen("A.in","w",stdout);
	srand(time(0));
	int n = 4;
	printf("%d\n",n);
	for(int i = 1; i <= n; i ++)
		printf("%d %d\n",rand()%N, rand()%N);
	return 0;
}
