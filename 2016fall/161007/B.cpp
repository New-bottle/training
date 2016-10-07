#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

std::unordered_set<std::string> xset;

int main()
{
	int T;
	std::cin >> T;
	std::string line;
	std::getline(std::cin, line);
	for (int i = 0; i < T; ++i) {
		xset.clear();
		std::vector<std::string> text;
		std::getline(std::cin, line);
		std::istringstream iss(line);
		while (1) {
			std::string word;
			iss >> word;
			if (!iss)
				break;
			text.push_back(word);
		}
		while (std::getline(std::cin, line)) {
			std::istringstream iss(line);
			std::string word;
			iss >> word;
			iss >> word;
			if (word == "does")
				break;
			iss >> word;
			xset.insert(std::move(word));
		}
		std::vector<std::string> ans;
		for (auto& w : text) {
			if (!xset.count(w))
				ans.push_back(w);
		}
		if (ans.empty()) {
			std::cout << std::endl;
			continue;
		}
		for (int i = 0; i < (int) ans.size(); ++i) {
			std::cout << ans[i] << " \n"[i == ans.size() - 1];
		}
	}
}
