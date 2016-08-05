#include <stdio.h>
#include "stdlib.h"

long long w[110000][2],d[110000],ed[110000][3],tot[3],col[110000],edg[110000];

int comp(const void *a,const void *b){
    long long t;
    t=((long long *)a)[0]-((long long *)b)[0];
    if (t>0){
        return 1;
    }
    else {
        if (t<0){
            return -1;
        }
        else {
            return 0;
        }
    }
}

int main(){
	freopen("D.in","r",stdin);
//	freopen("D.ans","w",stdout);
    long long n,m,i,j,k,t,test,q,x,y;
    char s[100];
    test=0;
    while (scanf("%lld%lld",&n,&m)!=EOF){
        test++;
        for (i=1;i<=n;i++){
            scanf("%lld",col+i);
        }
        for (i=0;i<m;i++){
            scanf("%lld%lld%lld",ed[i],ed[i]+1,ed[i]+2);
            if (ed[i][0]>ed[i][1]){
                t=ed[i][0];
                ed[i][0]=ed[i][1];
                ed[i][1]=t;
            }
        }
        qsort(ed,m,sizeof(long long )*3,comp);
        for (i=1,k=0;i<m;i++){
            if (ed[i][0]==ed[i-1][0]&&ed[i][1]==ed[i-1][1]){
                k++;
                ed[i-k][2]+=ed[i][2];
            }
            else {
                ed[i-k][0]=ed[i][0];
                ed[i-k][1]=ed[i][1];
                ed[i-k][2]=ed[i][2];
            }
        }
        m-=k;
        for (i=1;i<=n;i++){
            d[i]=0;
            w[i][0]=0;
            w[i][1]=0;
        }
        for (i=0;i<m;i++){
            d[ed[i][0]]++;
            d[ed[i][1]]++;
        }
        for (i=0;i<m;i++){
            if (d[ed[i][0]]>d[ed[i][1]]){
                t=ed[i][0];
                ed[i][0]=ed[i][1];
                ed[i][1]=t;
            }
        }
        qsort(ed, m, sizeof(long long )*3,comp);
        ed[m][0]=n+1;
        for (i=1,j=0;i<=n;i++){
            edg[i]=j;
            while (ed[j][0]==i){
                j++;
            }
        }
        edg[n+1]=m;
        tot[0]=0;
        tot[1]=0;
        tot[2]=0;
        for (i=0;i<m;i++){
            if (col[ed[i][0]]!=col[ed[i][1]]){
                tot[2]+=ed[i][2];
            }
            else {
                tot[col[ed[i][0]]]+=ed[i][2];
            }
            w[ed[i][1]][col[ed[i][0]]]+=ed[i][2];
        }
        scanf("%lld",&q);
        printf("Case %lld:\n",test);
        for (i=0;i<q;i++){
            scanf("%s",s);
            if (s[0]=='A'){
                scanf("%lld%lld",&x,&y);
                if (x!=y){
                    printf("%lld\n",tot[2]);
                }
                else {
                    printf("%lld\n",tot[x]);
                }
            }
            else {
                scanf("%lld",&x);
                y=col[x];
                tot[y]-=w[x][y];
                tot[1-y]+=w[x][1-y];
                tot[2]+=w[x][y]-w[x][1-y];
                for (j=edg[x];j<edg[x+1];j++){
                    w[ed[j][1]][y]-=ed[j][2];
                    w[ed[j][1]][1-y]+=ed[j][2];
                    if (y==col[ed[j][1]]){
                        tot[y]-=ed[j][2];
                        tot[2]+=ed[j][2];
                    }
                    else {
                        tot[1-y]+=ed[j][2];
                        tot[2]-=ed[j][2];
                    }
                }
                col[x]=1-y;
            }
        }
    }
    return 0;
}
