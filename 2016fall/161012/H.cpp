#include<cstdio>
#include<vector>
#include<cstdlib>
using namespace std;

#define maxn (2010)
int T,K,mi[5] = {1,10,100,1000},len; vector <int> vec[15];
bool exist[maxn];

inline void dfs(int now,int step,int res)
{
	if (now == 10) { exist[res] = true; return; }
	for (int i = 0;i < vec[now].size();++i)
	{
		int nxt = vec[now][i];
		dfs(nxt,step,res);
		for (int j = 1;j <= 3-step;++j)
		{
			int num = 0;
			for (int k = 1;k <= j;++k) num = num*10+now;
			dfs(nxt,step+j,res*mi[j]+num);
		}
	}
}

int main()
{
	// freopen("H.in","r",stdin);
	// freopen("H.out","w",stdout);
	scanf("%d",&T);
	vec[1].push_back(2); vec[1].push_back(4);
	vec[2].push_back(3); vec[2].push_back(5);
	vec[3].push_back(6); vec[3].push_back(10);
	vec[4].push_back(5); vec[4].push_back(7);
	vec[5].push_back(6); vec[5].push_back(8);
	vec[6].push_back(9); vec[6].push_back(10);
	vec[7].push_back(8); vec[7].push_back(10);
	vec[8].push_back(0); vec[8].push_back(9);
	vec[9].push_back(10); vec[0].push_back(10);
	dfs(1,0,0);
	for (int i = 0;i < 1000;++i) if (exist[i]) printf("%d\n",i);
	while (T--)
	{
		scanf("%d",&K);
		for (int i = 0;;++i)
		{
			if (exist[K+i]) { printf("%d\n",K+i); break; }
			if (K-i >= 0&&exist[K-i]) { printf("%d\n",K-i); break; }
		}
	}
	// fclose(stdin); fclose(stdout);
	return 0;
}
