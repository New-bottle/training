#include<cstring>
#include<cstdio>
#include<cstdlib>
using namespace std;

#define rhl (10007)
#define maxn (1010)
int T,N,f[maxn][maxn],ans; char s[maxn];

int main()
{
	// freopen("A.in","r",stdin);
	scanf("%d\n",&T);
	for (int p = 1;p <= T;++p)
	{
		printf("Case %d: ",p);
		scanf("%s\n",s+1); N = strlen(s+1);
		memset(f,0,sizeof(f)); ans = 0;
		for (int i = 1;i <= N;++i) f[i][i] = 1;
		for (int i = 2;i <= N;++i)
			for (int j = 1;j+i-1 <= N;++j)
			{
				f[j][j+i-1] = f[j+1][j+i-1]+f[j][j+i-2]-f[j+1][j+i-2];
				if (s[j] == s[j+i-1]) f[j][j+i-1] += f[j+1][j+i-2];
				f[j][j+i-1] %= rhl;
				if (f[j][j+i-1] < 0) f[j][j+i-1] += rhl;
			}
		ans += f[1][N];
		memset(f,0,sizeof(f));
		for (int i = 2;i <= N;++i)
			for (int j = 1;j+i-1 <= N;++j)
			{
				f[j][j+i-1] = f[j+1][j+i-1]+f[j][j+i-2]-f[j+1][j+i-2];
				if (s[j] == s[j+i-1]) f[j][j+i-1] += f[j+1][j+i-2]+1;
				f[j][j+i-1] %= rhl;
				if (f[j][j+i-1] < 0) f[j][j+i-1] += rhl;
			}
		ans += f[1][N]; if (ans >= rhl) ans -= rhl;
		printf("%d\n",ans);
	}
	return 0;
}
