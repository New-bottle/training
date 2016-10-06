#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,m,q;
int num[maxn*8];
int siz=0;
vector<pair<int,int> >MM;
int id(int x){
	return lower_bound(MM.begin(),MM.end(),make_pair(x,-1))->second;
	//return M[x];
}

struct adder{
	int l,r,v;
	bool operator<(adder oth)const{
		return v<oth.v;
	}
}A[maxn];

struct qes{
	int l,r;long long k;
	int id;
	long long tmp;
}Q[maxn];
int anss[maxn];

struct node{
	int l,r;
	long long sum;
	long long add;
	inline long long len()const{return r-l+1;}
	node(){sum=add=0;}
}t[maxn*32];
vector<pair<int,int> >vec;
int nn;
void rz(int i){
	t[i].sum=t[i<<1].sum+t[i<<1|1].sum;
}
void pd(int i,int l,int r){
	if(t[i].add){
		t[i<<1].add+=t[i].add;
		t[i<<1].sum+=t[i].add*t[i<<1].len();
		
		t[i<<1|1].add+=t[i].add;
		t[i<<1|1].sum+=t[i].add*t[i<<1|1].len();
		
		t[i].add=0;
	}
}
void build(int i,int l,int r){
	if(l==r){
		t[i].l=vec[l-1].first;
		t[i].r=vec[l-1].second;
		return ;
	}
	int mid=(l+r)>>1;
	build(i<<1,l,mid);
	build(i<<1|1,mid+1,r);
	rz(i);
	t[i].l=t[i<<1].l;
	t[i].r=t[i<<1|1].r;
}
void Add(const int &i,const int &l,const int &r,const int &l0,const int &r0,const long long &x){
	//printf("%d %d %d %d %d %d\n",i,l,r,l0,r0,x);
	if(l0<=l&&r0>=r){
		t[i].add+=x;
		t[i].sum+=x*t[i].len();
		return ;	
	}
	pd(i,l,r);
	int mid=(l+r)>>1;
	if(l0<=mid)Add(i<<1,l,mid,l0,r0,x);
	if(r0>mid)Add(i<<1|1,mid+1,r,l0,r0,x);
	rz(i);
}
long long Sum(const int &i,const int &l,const int &r,const int &l0,const int &r0){
	if(l0<=l&&r0>=r){
		return t[i].sum;
	}
	pd(i,l,r);
	int mid=(l+r)>>1;
	long long ans=0;
	if(l0<=mid)ans+=Sum(i<<1,l,mid,l0,r0);
	if(r0>mid)ans+=Sum(i<<1|1,mid+1,r,l0,r0);
	return ans;
}

bool part(qes q){
	return q.tmp<q.k;
}

void solve(int l0,int r0,int l1,int r1){
	if(l0>r0||l1>r1)
		return;
	if(l1==r1){
		for(int i=l0;i<=r0;i++)
			anss[Q[i].id]=A[l1].v;		
		return ;
	}
	int m1=(l1+r1)>>1;
	for(int i=l1;i<=m1;i++)
		Add(1,1,nn,id(A[i].l),id(A[i].r),1);
	for(int i=l0;i<=r0;i++)
		Q[i].tmp=Sum(1,1,nn,id(Q[i].l),id(Q[i].r));
	int m0=stable_partition(Q+l0,Q+r0+1,part)-Q-1;
	solve(l0,m0,m1+1,r1);
	for(int i=l1;i<=m1;i++){
		Add(1,1,nn,id(A[i].l),id(A[i].r),-1);
	}
	solve(m0+1,r0,l1,m1);
}

int getn(){
	int r=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r;
}
long long getLL(){
	long long r=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r;
}

int main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=m;i++){
		//scanf("%d%d%d",&A[i].l,&A[i].r,&A[i].v);
		A[i].l=getn();
		A[i].r=getn();
		A[i].v=getn();
		num[++siz]=A[i].l;
		num[++siz]=A[i].r;
	}	
	for(int i=1;i<=q;i++){
		//scanf("%d%d%lld",&Q[i].l,&Q[i].r,&Q[i].k);
		Q[i].l=getn();
		Q[i].r=getn();
		Q[i].k=getLL();
		Q[i].id=i;
		num[++siz]=Q[i].l;
		num[++siz]=Q[i].r;
	}
	sort(A+1,A+1+m);
	sort(num+1,num+1+siz);
	siz=unique(num+1,num+1+siz)-num-1;
	for(int i=1;i<=siz;i++){
		vec.push_back(make_pair(num[i],num[i]));
		if(i!=siz&&num[i]+1<=num[i+1]-1)
			vec.push_back(make_pair(num[i]+1,num[i+1]-1));
	}
	nn=vec.size();
	for(int i=0;i<vec.size();i++){
		if(vec[i].first==vec[i].second){
			MM.push_back(make_pair(vec[i].first,i+1));
		}
	}
	build(1,1,nn);	
	solve(1,q,1,m);
	
	for(int i=1;i<=q;i++)
		printf("%d\n",anss[i]);
	
	return 0;
}
