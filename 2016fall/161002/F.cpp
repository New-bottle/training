#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#define N 1010
using namespace std;
int a[N];
int main(){
	int n, p, k, d;
	scanf("%d%d%d%d", &n, &p, &k, &d);
	int sum = (d - 1) * d / 2;
	if(d == 1){
		if(n == k){
			if(p % n == 0){
				for(int i = 1; i <= n; i ++){
					printf("%d\n", p / n);
				}
			}
			else{
				puts("Wrong information");
			}
		}
		else{
			int m = n - k;
			int num1 = p / k;
			int num2 = ((p - k * num1) + (m - 1)) / m;
			if(num2 > num1) puts("Wrong information");
			else{
				for(int i = 1; i <= k; i ++) printf("%d\n", num1);
				int tmp = 0;
				for(int i = k + 1; i <= n; i ++){
					if(tmp >= p - k * num1){
						puts("0");
					}
					else if(tmp + num2 > p - k * num1){
						printf("%d\n", p - k * num1 - tmp);
					}
					else printf("%d\n", num2);
					tmp += num2;
				}
			}
		}
		return 0;
	}
	if(p < sum){
		puts("Wrong information");
	}
	else{
		int cur = 0;
		for(int i = 1; i <= k; i ++){
			if(i <= k - d + 1) a[i] = 0;
			else if(i != k){
				a[i] = k - i + 1;
				cur += k - i + 1;
			}
		}
		a[k] = p - cur;
		for(int i = k + 1; i <= n; i ++) a[i] = 0;
		sort(a + 1, a + n + 1);
		for(int i = n; i; i --){
			printf("%d\n", a[i]);
		}
	}
}
