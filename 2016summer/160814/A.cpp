#include <iostream>

#include <string>

int main()
{
    int kase = 0;
    std::ios::sync_with_stdio(false);
    std::string s;
    while (std::getline(std::cin, s) && !s.empty()) {
        int a = 0, b = 0;
        for (unsigned i = 0; i < s.size(); ++i) {
            a = a * 10 + s[i] - '0';
            b = b * 10 + s[i] - '0';
            if (a >= 137)
                a %= 137;
            if (b >= 73)
                b %= 73;
        }
        std::cout << "Case #" << ++kase << ": " << (a == 0 && b == 0 ? "YES" : "NO") << std::endl;
    }
    return 0;
}
