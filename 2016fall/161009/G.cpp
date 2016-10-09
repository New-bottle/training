#include<cmath>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
using namespace std;

#define len (222)
#define maxn (100010)
int exist[maxn]; int T,N,Q,num,seq[maxn],ans[maxn];
inline int gi()
{
	int ret = 0,f = 1; register char ch;
	do ch = getchar(); while (!(ch >= '0' && ch <= '9')&&ch != '-');
	if (ch == '-') f = -1,ch = getchar();
	do ret = ret*10+ch-'0',ch = getchar(); while (ch >= '0'&&ch <= '9');
	return ret*f;
}
struct node
{
	int id,pos,l,r;
	friend inline bool operator <(const node &a,const node &b) { return a.pos != b.pos ?a.pos < b.pos:a.r < b.r; }
	inline void read(int i) { id = i; l = gi(); r = gi(); pos = (l+len-1) / len; }
}query[maxn];

int main()
{
	freopen("G.in","r",stdin);
	freopen("G.out","w",stdout);
	for (int T = gi();T--;)
	{
		N = gi(); Q= gi();
		for (int i = 1;i <= N;++i) seq[i] = gi();
		memset(exist,0,4*(N+1)); num = 0;
		for (int i = 1;i <= Q;++i) query[i].read(i);
		sort(query+1,query+Q+1);
		for (int i = 1,l = 1,r = 0,now;i <= Q;++i)
		{
			while (l > query[i].l)
			{
				now = seq[--l];
				++num; exist[now] = 1;
				num -= exist[now+1]+exist[now-1];
			}
			while (r < query[i].r)
			{
				now = seq[++r];
				++num; exist[now] = 1;
				num -= exist[now+1]+exist[now-1];
			}
			while (l < query[i].l)
			{
				now = seq[l++];
				--num; exist[now] = 0;
				num += exist[now+1]+exist[now-1];
			}
			while (r > query[i].r)
			{
				now = seq[r--];
				--num; exist[now] = 0;
				num += exist[now+1]+exist[now-1];
			}
			ans[query[i].id] = num;
		}
		for (int i = 1;i <= Q;++i) printf("%d\n",ans[i]);
	}
	fclose(stdin); fclose(stdout);
	return 0;
}
