#include<algorithm>
#include<queue>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
using namespace std;

typedef long long ll;
#define maxn (10010)
#define maxm (300010)
#define inf (1<<30)
int cnt,ch[maxm*2][2],fa[maxm*2],mi[maxm*2],b[maxm],root[maxm];
int pmi[maxm*2],key[maxm*2],stack[maxm*2],T,N,M,Q,tot;
ll ans; bool rev[maxm*2]; queue <int> team;

inline int gi()
{
	int ret = 0,f = 1; char ch;
	do ch = getchar(); while (!(ch >= '0'&&ch <= '9')&&ch != '-');
	if (ch == '-') f = -1;
	do ret = ret*10+ch-'0',ch = getchar(); while (ch >= '0'&&ch <= '9');
	return ret*f;
}
struct EDGE
{
	int u,v,w;
	inline void read() { u = gi(),v = gi(),w = gi(); }
	friend inline bool operator <(const EDGE &a,const EDGE &b) { return a.w < b.w; }
}edge[maxm];
struct SEG { ll sum; int lc,rc; }tree[maxm*30];

inline bool isroot(int x) { return ch[fa[x]][0] != x&&ch[fa[x]][1] != x; }
inline void updata(int x)
{
	int lc = ch[x][0],rc = ch[x][1];
	mi[x] = key[x]; pmi[x] = x;
	if (lc && mi[lc] < mi[x]) mi[x] = mi[lc],pmi[x] = pmi[lc];
	if (rc && mi[rc] < mi[x]) mi[x] = mi[rc],pmi[x] = pmi[rc];
}
inline int newnode(int w)
{
	int ret;
	if (team.empty()) ret = ++cnt; else ret = team.front(),team.pop();
	key[ret] = w; fa[ret] = ch[ret][0] = ch[ret][1] = 0;
	updata(ret); return ret;
}
inline void rotate(int x)
{
	int y = fa[x],z = fa[y],l = ch[y][1] == x,r = l ^ 1;
	if (!isroot(y)) ch[z][ch[z][1] == y] = x; fa[x] = z;
	if (ch[x][r]) fa[ch[x][r]] = y; ch[y][l] = ch[x][r];
	fa[y] = x; ch[x][r] = y; updata(y); updata(x);
}
inline void pushdown(int x)
{
	if (rev[x])
	{
		int lc = ch[x][0],rc = ch[x][1];
		rev[x] = false; swap(ch[x][0],ch[x][1]);
		if (lc) rev[lc] ^= 1; if (rc) rev[rc] ^= 1;
	}
}
inline void splay(int x)
{
	int top = 0,i;
	for (i = x;!isroot(i);i = fa[i]) stack[++top] = i; stack[++top] = i;
	while (top) pushdown(stack[top--]);
	while (!isroot(x))
	{
		int y = fa[x],z = fa[y];
		if (!isroot(y))
		{
			if ((ch[y][0] == x)^(ch[z][0] == y)) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
}
inline int access(int x) { int t = 0; for (;x;t = x,x = fa[x]) splay(x),ch[x][1] = t,updata(x); return t; }
inline int evert(int x) { int t = access(x); rev[t] ^= 1; return t; }
inline int find(int x) { int t = access(x); while (pushdown(t),ch[t][0]) t = ch[t][0]; return t; }
inline void cut(int now)
{
	evert(now); team.push(now);
	access(edge[key[now]].u); splay(now); ch[now][1] = fa[edge[key[now]].u] = 0;
	access(edge[key[now]].v); splay(now); ch[now][1] = fa[edge[key[now]].v] = 0;
}
inline void link(int w)
{
	if (find(edge[w].u) == find(edge[w].v))
	{
		evert(edge[w].u); int t = access(edge[w].v);
		b[w] = mi[t]; cut(pmi[t]);
	}
	else b[w] = 0;
	int now = newnode(w);
	int t1 = evert(edge[w].u),t2 = evert(edge[w].v); fa[t1] = fa[t2] = now;
}

inline int lb(int key)
{
	int l = 1,r = M,mid;
	while (l <= r)
	{
		mid = (l+r)>>1;
		if (edge[mid].w >= key) r = mid-1;
		else l = mid+1;
	}
	return l;
}
inline int ub(int key)
{
	int l = 1,r = M,mid;
	while (l <= r)
	{
		mid = (l+r) >> 1;
		if (edge[mid].w <= key) l = mid+1;
		else r = mid-1;
	}
	return l;
}

inline void build(int &now,int l,int r)
{
	now = ++tot;
	if (l == r) return; int mid = (l+r) >> 1;
	build(tree[now].lc,l,mid); build(tree[now].rc,mid+1,r);
}
inline void insert(int pos,int l,int r,int ref,int &now,int inc)
{
	now = ++tot; tree[now]= tree[ref]; tree[now].sum += (ll)inc;
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (pos <= mid) insert(pos,l,mid,tree[ref].lc,tree[now].lc,inc);
	else insert(pos,mid+1,r,tree[ref].rc,tree[now].rc,inc);
}
inline ll query(int now,int l,int r,int ql,int qr)
{
	if (ql == l&&qr == r) return tree[now].sum;
	int mid = (l+r)>>1;
	if (mid >= qr) return query(tree[now].lc,l,mid,ql,qr);
	else if (ql > mid) return query(tree[now].rc,mid+1,r,ql,qr);
	else return query(tree[now].lc,l,mid,ql,mid)+query(tree[now].rc,mid+1,r,mid+1,qr);
}

inline void init()
{
	ans = tot = 0;
	memset(ch,0,sizeof(ch)); memset(fa,0,sizeof(fa));
	memset(pmi,0,sizeof(pmi)); memset(rev,false,sizeof(rev));
}

int main()
{
	//freopen("9826.in","r",stdin);
	//freopen("9826.out","w",stdout);
	scanf("%d",&T);
	while (T--)
	{
		cnt = N = gi(); M = gi(); init();
		for (int i = 1;i <= M;++i) edge[i].read();
		for (int i = 1;i <= N;++i) key[i] = inf;
		sort(edge+1,edge+M+1);
		for (int i = 1;i <= M;++i) link(i);
		build(root[0],1,M+1);
		for (int i = 1;i <= M;++i)
			insert(b[i]+1,1,M+1,root[i-1],root[i],edge[i].w);
		for (Q = gi();Q--;)
		{
			int l = gi(),r = gi();
//			l -= ans; r -= ans; 
			l = lb(l); r = ub(r)-1;
			printf("%lld\n",ans = query(root[r],1,M+1,1,l)-query(root[l-1],1,M+1,1,l));
		}
	}
	//fclose(stdin); fclose(stdout);
	return 0;
}
