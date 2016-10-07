#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <utility>
#include <queue>

std::unordered_map<std::string, int> mapping;
int n;

const int N = 400000;
const int M = 200000;

std::vector<std::pair<int, int>> pts2line[N];
std::vector<int> line2pts[M];
int gm;

int src, dst;

void init()
{
	mapping.clear();
	gm = 0;
}

void addstops(const std::string& line)
{
	n = 0;
	std::istringstream iss(line);
	std::string s;
	iss >> s;
	while (1) {
		iss >> s;
		if (!iss)
			break;
		if (s.back() == ',')
			s.pop_back();
		mapping[s] = ++n;
	}
	for (int i = 0; i <= n; ++i)
		pts2line[i].clear();

}

int noln;

void addlines(const std::string& line)
{
	std::istringstream iss(line);
	std::string s;
	iss >> s;
	int m = 0;
	while (1) {
		iss >> s;
		if (!iss)
			break;
		++m;
	}
	noln = m;
	for (int i = 0; i <= m; ++i)
		line2pts[i].clear();
}

void addnewline(const std::string& line)
{
	std::istringstream iss(line);
	std::string s;
	iss >> s;
	iss >> s;
	int k = ++gm;
	int i = 0;
	while (1) {
		iss >> s;
		if (!iss)
			break;
		if (s.back() == ',')
			s.pop_back();
		int ptid = mapping.at(s);
		line2pts[k].push_back(ptid);
		pts2line[ptid].emplace_back(k, i);
		++i;
	}
}

int getlive(const std::string& line)
{
	std::istringstream iss(line);
	std::string s;
	iss >> s;
	iss >> s;
	iss >> s;
	iss >> s;
	return mapping.at(s);
}

int ptslayer[N];
int1

void work()
{
}

int main()
{
	int T;
	std::cin >> T;
	std::string line;
	std::getline(std::cin, line);
	for (int t = 0; t < T; ++t) {
		init();
		std::getline(std::cin, line);
		std::getline(std::cin, line);
		addstops(line);
		std::getline(std::cin, line);
		addlines(line);
		for (int i = 0; i < noln; ++i) {
			std::getline(std::cin, line);
			addnewline(line);
		}
		std::getline(std::cin, line);
		src = getlive(line);
		std::getline(std::cin, line);
		dst = getlive(line);
		work();
	}
	std::ios::sync_with_stdio(false);
}
