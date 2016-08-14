#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#define MOD 1000000007LL
#define LL long long
#define M 2010
#define N 401
using namespace std;
int prime[M];
bool is_prime[M]; 
LL fac[N];
LL data[N];
void init(){
    int m = 2000;
    for(int i = 2; i <= m; i ++) is_prime[i] = 1;
    for(int i = 2; i <= m; i ++){
        if(is_prime[i]){
            prime[++ prime[0]] = i;   
        }
        for(int j = 1; j <= prime[0] && prime[j] * i <= m; j ++){
            is_prime[prime[j] * i] = 0;
            if(i % prime[j] == 0) break;   
        }
    }
}
int n;
int a[N][N];
int gause(){
    int m = prime[0];
    int i, j, k;
    for(i = 1, j = 1; i <= m && j <= n; i ++, j ++){
        int max_r = i;
        for(k = i + 1; k <= m; k ++){
            if(a[k][j] > a[max_r][j]) max_r = k;
        }
        if(max_r != i){
            for(k = j; k <= n + 1; k ++) swap(a[max_r][k], a[i][k]);
        }
        if(a[i][j] == 0){
            i --;
            continue;
        }
        for(k = i + 1; k <= m; k ++){
            if(!a[k][j]) continue;
            for(int p = j; p <= n + 1; p ++){
                a[k][p] = a[k][p] ^ a[i][p];
            }
        }
    }
    int res = n - (i - 1);
    return res;
}
void solve(){
    scanf("%d", &n);
    
       memset(a, 0, sizeof(a));
    
    for(int i = 1; i <= n; i ++){
        scanf("%I64d", &data[i]);    
        for(int j = 1; j <= prime[0]; j ++){
            if(data[i] % prime[j] == 0){
                int tot = 0;
                LL tmp = data[i];
                while(tmp % prime[j] == 0){
                    tmp = tmp / prime[j];
                    tot ++;
                }
                a[j][i] = (tot & 1);
            } 
        }
    }
    int t = gause();
    LL ans = fac[t] % MOD;
    printf("%I64d\n", (ans - 1 + MOD) % MOD);
}
int main(){
    init();
    for(int i = fac[0] = 1; i <= 400; i ++) fac[i] = fac[i - 1] * 2 % MOD;
    int testcase;
    scanf("%d", &testcase);
    for(int i = 1; i <= testcase; i ++){
        printf("Case #%d:\n", i);
        solve();    
    }
    return 0;
}
