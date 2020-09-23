#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

int main()
{
    std::map <char, std::vector<std::string> > rules;
    std::set<char> reachable, newsym;
    std::string left, right;

    while (std::cin >> left >> right) {
        rules.try_emplace(left[0]);
        rules[left[0]].push_back(right);
    }
    left.clear();
    right.clear();

    newsym.insert('S');

    while (newsym != reachable) {
        reachable = newsym;
        for (auto c : reachable) {
            for (auto &r : rules[c]) {
                for (auto j : r) {
                    if (j >= 'A' && j <= 'Z') {
                        newsym.insert(j);
                    }
                }
            }
        } 
    }

    for (auto i : reachable) {
        for (auto &r : rules[i]) {
            std::cout << i << " " << r << std::endl;
        }
    }

    return 0;
}
