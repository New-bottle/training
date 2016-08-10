#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

char s[1000];
int main(){
	freopen("chemist.txt","r",stdin);
	freopen("chemist.out","w",stdout);
	printf("dic[200][5] = {");
	while(scanf("%s", s) != EOF){
		printf("\"");
		for(int i = 0; i < strlen(s); i ++)
			if (s[i] >= 'a' && s[i] <= 'z') printf("%c", s[i]);
			else printf("%c", s[i] - 'A' + 'a');
		printf("\",");
	}
	return 0;
}
