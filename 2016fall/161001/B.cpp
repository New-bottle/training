#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string input;

#define output do { for (int i = 0; i < indent; ++i) \
	std::cout << ' '; std::cout << buf << '\n'; } while (0)

int work(int p)
{
	enum State {
		START,
		TAG,
		CLOSING,
		CLOSING2,
		OPENING,
		OPENING2,
		SELF,
		TEXT
	} state = START;
	std::string buf;
	int indent = 0;
	while (1) {
		char ch = input[p];
		++p;
		switch (state) {
		case START:
			if (ch == '<') {
				buf += ch;
				state = TAG;
			}
			break;
		case TAG:
			buf += ch;
			if (ch == '/') {
				state = CLOSING;
			} else {
				state = OPENING;
			}
			break;
		case CLOSING:
			buf += ch;
			if (ch == '"') {
				state = CLOSING2;
			} else if (ch == '>') {
				--indent;
				output;
				if (buf == "</html>")
					return p;
				buf.clear();
				state = TEXT;
			}
			break;
		case CLOSING2:
			buf += ch;
			if (ch == '"')
				state = CLOSING;
			break;
		case OPENING:
			buf += ch;
			if (ch == '"') {
				state = OPENING2;
			} else if (ch == '/') {
				state = SELF;
			} else if (ch == '>') {
				output;
				buf.clear();
				state = TEXT;
				++indent;
			}
			break;
		case OPENING2:
			buf += ch;
			if (ch == '"')
				state = OPENING;
			break;
		case SELF:
			buf += ch;
			assert(ch == '>');
			output;
			buf.clear();
			state = TEXT;
			break;
		case TEXT:
			if (ch == '<') {
				std::istringstream ss(buf);
				buf.clear();
				std::vector<std::string> v;
				std::string s;
				while (ss >> s)
					v.push_back(std::move(s));
				if (v.size()) {
					for (int i = 0; i < indent; ++i)
						std::cout << ' ';
					for (int i = 0; i < (int) v.size(); ++i)
						std::cout << v[i] << " \n"[i == v.size() - 1];
				}
				buf += ch;
				state = TAG;
			} else {
				buf += ch;
			}
			break;
		default:
			assert(0);
		}
	}
}

int main()
{
	std::ios::sync_with_stdio(false);
	int t;
	std::cin >> t;
	std::string line;
	std::getline(std::cin, line);
	while (std::getline(std::cin, line)) {
		input += line;
		input += '\n';
	}
	int p = 0;
	for (int i = 1; i <= t; ++i) {
		std::cout << "Case #" << i << ":\n";
		p = work(p);
	}
	return 0;
}
