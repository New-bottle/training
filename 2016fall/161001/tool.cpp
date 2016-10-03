#include<iostream>
#include<cstdio>
#define LL long long
using namespace std;
int main(){
	double a = 1, b = 1;
	for(int i = 0; i <= 8; i ++, a = a * 1000, b = b * 1024){
		cout << 1 - (1.0 * a / b) << endl;
	}
}
