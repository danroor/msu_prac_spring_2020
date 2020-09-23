#include <iostream>
#include <string>
#include <vector>
#include <map>

int main()
{
    std::map <char, std::vector<std::string> > rules;
    std::vector<char> reachable;
    std::string left, right;

    while (std::cin >> left >> right) {
        rules.try_emplace(left[0]);
        rules[left[0]].push_back(right);
    }

    reachable.push_back('S');
    int cnt = 0, prev = -1;
    char c;

    do {
        prev++;
        c = reachable[prev];
        for (auto &r : rules[c]) {
            for (auto j : r) {
                if (j >= 'A' && j <= 'Z') {
                    reachable.push_back(j); 
                    cnt++;
                }
            }
        }

    } while (prev < cnt);

    for (auto i : reachable) {
        for (auto &r : rules[i]) {
            std::cout << i << " " << r << std::endl;
        }
    }

    return 0;
}
