#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

typedef long long ll;
#define maxn (100010)
int T,N,tot,prime[maxn];

inline void ready()
{
	for (int i = 2;i <= 100000;++i)
		if (!prime[i])
		{
			prime[++tot] = i;
			for (ll j = (ll)i*(ll)i;j <= 100000;j += i) prime[j] = 1;
		}
}

int main()
{
	//freopen("C.in","r",stdin);
	//freopen("C.out","w",stdout);
	scanf("%d",&T); ready();
	while (T--)
	{
		scanf("%d",&N);
		if(N == 1){
			puts("IMPOSSIBLE");
			continue;
		}
		if (N&1) printf("%d = %d + %d\n",N,(N-1)>>1,(N+1)>>1);
		else
		{
			int now = N<<1,p = 0,q = 0,a,b,len;
			while (!(now & 1)) ++p,now >>= 1;
			p = 1<<p;
			for (int i = 2;prime[i]*prime[i] <= now;++i)
				if (!(now % prime[i])) { q = prime[i]; break; }
			if (!q ) q = now;
			len = min(p,q);
			if (len == 1) { printf("IMPOSSIBLE\n"); continue; }
			a = (2LL*(ll)N-(ll)(len+1)*(ll)len)/(2LL*(ll)len);
			b = (2LL*(ll)N+(ll)(len-1)*(ll)len)/(2LL*(ll)len);
			/*
			if(a <= 0 || b <= 0 || b <= a + 1){
				puts("IMPOSSIBLE");
				continue;
			}
			*/
			printf("%d = %d",N,a+1);
			for (int i = a+2;i <= b;++i) printf(" + %d",i);
			puts("");
		}
	}
	//fclose(stdin); fclose(stdout);
	return 0;
}
