#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int N = 100010;
int test;
char name[100] = "galaxy", tmp[100], in[100];

void ready() {
	strcpy(tmp, name);
	int l = strlen(tmp);
	tmp[l] = test + '0';
	strcpy(in, tmp);
	strcat(in, ".in");
	freopen(in, "w", stdout);
}
void finish() {
	fclose(stdout);
	strcpy(tmp, name);
	strcat(tmp, " < ");
	strcat(tmp, in);
	strcat(tmp, " > ");
	strcat(tmp, name);
	int l = strlen(tmp);
	tmp[l] = test + '0';
	strcat(tmp, ".out");
	test ++;
//	puts(tmp);
	system(tmp);
	memset(tmp, 0, sizeof tmp);
}

void make20() {
}

void make40() {
}

void make100() {
}

int main(){
	for(int i = 1; i <= 2; i ++) {
		ready();
		make20();
		finish();
	}
	for(int i = 3; i <= 4; i ++) {
		ready();
		make40();
		finish();
	}
	for(int i = 5; i <= 10; i ++) {
		ready();
		make100();
		finish();
	}
	return 0;
}
