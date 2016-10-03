#include <algorithm>
#include <iostream>
#include <vector>

int arr[16];
int lis[16];
int n = 8;

inline int sign(int a)
{
	return a > 0 ? 1 : a < 0 ? -1 : 0;
}

struct Entry {
	std::vector<int> v;
	int info[5];
};
std::vector<Entry> ent;

int fa()
{
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			ans += arr[i] > arr[j];
		}
	}
	return ans;
}

int fb()
{
	int ans = 0;
	for (int i = 1; i < n; ++i) {
		if (arr[i] < arr[i - 1])
			++ans;
	}
	return ans;
}

int fc()
{
	int ans = 1;
	lis[0] = 1;
	for (int i = 1; i < n; ++i) {
		lis[i] = 1;
		for (int j = 0; j < i; ++j) {
			if (arr[i] > arr[j])
				lis[i] = std::max(lis[i], lis[j] + 1);
		}
		ans = std::max(ans, lis[i]);
	}
	return ans;
}

int fd()
{
	int ans = 1;
	int bns = 1;
	for (int i = 1; i < n; ++i) {
		if (arr[i] > arr[i - 1])
			++bns;
		else
			bns = 1;
		ans = std::max(ans, bns);
	}
	return ans;
}

int fe()
{
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		if (arr[i] == i + 1)
			++ans;
	}
	return ans;
}

bool found[300];
int ans[300][2];

void findall()
{
	for (int i = 0; i < (int) ent.size(); ++i) {
		for (int j = 0; j < (int) ent.size(); ++j) {
			int a = ent[i].info[0] - ent[j].info[0];
			int b = ent[i].info[1] - ent[j].info[1];
			int c = ent[i].info[2] - ent[j].info[2];
			int d = ent[i].info[3] - ent[j].info[3];
			int e = ent[i].info[4] - ent[j].info[4];
			if (d == -1 || d == 1)
				continue;
			a = sign(a) + 1;
			b = sign(b) + 1;
			c = sign(c) + 1;
			d = sign(d) + 1;
			e = sign(e) + 1;
			int v = a + b * 3 + c * 9 + d * 27 + e * 81;
			if (found[v])
				continue;
			found[v] = true;
			ans[v][0] = i;
			ans[v][1] = j;
		}
	}
}

void print(int id)
{
	auto& v = ent[id].v;
	std::cout << "{";
	for (int i = 0; i < (int) v.size(); ++i) {
		std::cout << v[i] << ",,"[i == (int) v.size() - 1];
	}
	std::cout << "},";
}

void printcase(int k)
{
	const char s[] = "<=>";
	std::cout << '"';
	for (int i = 0; i < 5; ++i) {
		std::cout << s[k % 3];
		k /= 3;
	}
	std::cout << "\",";
}

int main()
{
	for (int i = 0; i < n; ++i) {
		arr[i] = i + 1;
	}
	do {
#if 0
		for (int i = 0; i < n; ++i) {
			std::cout << arr[i] << " \n"[i == n - 1];
		}
#endif
		ent.push_back({std::vector<int>(arr, arr + n), {fa(), fb(), fc(), fd(), fe()}});
#if 0
		std::cout << fa()
			<< '\t' << fb()
			<< '\t' << fc()
			<< '\t' << fd()
			<< '\t' << fe()
			<< std::endl;
#endif
	} while (std::next_permutation(arr, arr + n - 1));
	findall();
	for (int i = 0; i < 243; ++i) {
		std::cout << "{ ";
		printcase(i);
		std::cout << "{ ";
		if (!found[i]) {
			std::cout << "NOT FOUND" << std::endl;
		} else {
			print(ans[i][0]);
			print(ans[i][1]);
		}
		std::cout << "},";
		std::cout << "},\n";
	}
	return 0;
}
