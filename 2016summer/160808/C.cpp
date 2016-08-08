#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
const int N = 50010;

const char dic[200][5] = {"h","he","li","be","b","c","n","o","f","ne","na","mg","al","si","p","s","cl","ar","k","ca","sc","ti","v","cr","mn","fe","co","ni","cu","zn","ga","ge","as","se","br","kr","rb","sr","y","zr","nb","mo","tc","ru","rh","pd","ag","cd","in","sn","sb","te","i","xe","cs","ba","hf","ta","w","re","os","ir","pt","au","hg","tl","pb","bi","po","at","rn","fr","ra","rf","db","sg","bh","hs","mt","ds","rg","cn","fl","lv","la","ce","pr","nd","pm","sm","eu","gd","tb","dy","ho","er","tm","yb","lu","ac","th","pa","u","np","pu","am","cm","bk","cf","es","fm","md","no","lr"};

char s[N];
bool yes[N];

int main(){
	int T;
	scanf("%d", &T);
	while(T --){
		scanf("%s", s + 1);
		int n = strlen(s + 1);
		memset(yes, 0, sizeof yes);
		yes[0] = 1;
		for(int i = 0; i < n; i ++) if (yes[i]){
			for(int j = 0; j < 130; j ++){
				if (yes[i + 1] && yes[i + 2]) break;
				int k = strlen(dic[j]);
				if (k == 0) break;
				if (yes[i + k]) continue;
				bool sign = 1;
				for(int l = 0; l < k; l ++)
					if (s[i + 1 + l] != dic[j][l] || i + 1 + l > n){
						sign = 0; break;
					}
				if (sign) yes[i + k] = 1;
			}
		}
//		for(int i = 0; i <= n; i ++) printf("%d ", yes[i]); puts("");
		puts(yes[n] ? "YES" : "NO");
	}
	return 0;
}
