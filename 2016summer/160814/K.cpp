#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#define N 100010
using namespace std;
char str[N];
bool vis[30];
void solve(){
    int ans = 0;
    memset(vis, 0, sizeof(vis));
    scanf("%s", str);
    int len = strlen(str);
    for(int i = 0; i < len; i ++){
        if(!vis[str[i] - 'a']) ans ++;
        vis[str[i] - 'a'] = 1;
    }
    printf("%d\n", ans);
}
int main(){
    int testcase;
    scanf("%d", &testcase);
    for(int i = 1; i <= testcase; i ++){
        printf("Case #%d: ", i);
        solve();
    }
}
