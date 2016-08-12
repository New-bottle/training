#include<bits/stdc++.h>
using namespace std;
typedef long long LL;


LL a[23];
int K;
int len;
int TM=0;

struct sta{
	deque<int>dq;
	bool vis[15];
	sta(){
		dq.clear();
		memset(vis,0,sizeof vis);
	}
	void pop_front(){
		vis[dq.front()]=0;
		dq.pop_front();
	}
	void push_back(int x){
		dq.push_back(x);
		if(dq.size()>=K)
			pop_front();
		vis[x]=1;
	}
	bool exist(int x)const{
		return vis[x];
	}
	bool empty()const{
		return dq.empty();
	}
	LL hsh()const{
		LL r=0;
		for(int i=0;i<dq.size();i++)	
			r=r*10+dq[i]+1;
		return r;
	}
};

LL f[25][2][300020];
int vis[25][2][300020];
LL dfs(int l,bool up,const sta &S){
	if(l==len){
		return 1LL;
	}

	LL &ans=f[l][up][S.hsh()];
	if(vis[l][up][S.hsh()]==TM)
		return ans;
	vis[l][up][S.hsh()]=TM;
	ans=0;
	if(up){
		for(int i=0;i<=a[l];i++){
			if(S.exist(i))continue;
			sta nS=S;
			if(!S.empty() || i!=0)
				nS.push_back(i);
			ans+=dfs(l+1,up&&(i==a[l]),nS);
		}
	}else{
		for(int i=0;i<=9;i++){
			if(S.exist(i))continue;
			sta nS=S;
			if(!S.empty() || i!=0)
				nS.push_back(i);
			ans+=dfs(l+1,0,nS);
		}
	}
	return ans;
}


LL get(LL x){
	if(x==0)return 1;
	TM++;
	len=0;
	LL tx=x;
	while(tx)len++,tx/=10;
	for(int i=len-1;i>=0;i--){
		a[i]=x%10;
		x/=10;
		
	}
	
	LL ans=0;	
	for(int i=0;i<=a[0];i++){
		sta S;
		if(i)
			S.push_back(i);
		ans += dfs(1,i==a[0],S);
	}

	return ans;
}
int main(){
	freopen("GG.in","r",stdin);
	freopen("GG.ans","w",stdout);
	long long L,R;
	while(cin>>L>>R>>K){
		
		LL ans=get(R);
		//cerr<<get(R)<<endl;
		//cerr<<get(L-1)<<endl;
		
		ans-=get(L-1);
		
		cout << ans << endl;
	}
	return 0;
}
