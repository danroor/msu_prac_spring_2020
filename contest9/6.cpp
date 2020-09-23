#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <map>

int main()
{
    std::map < std::pair <std::string, char>, std::string > change;
    std::map <std::string, bool> isterm;
    std::string curstate, newstate;
    char c;

    std::cin >> curstate;
    while (curstate != "END") {
        isterm[curstate] = isterm[newstate] = false;
        std::cin >> c >> newstate;
        change[std::make_pair(curstate, c)] = newstate;
        std::cin >> curstate;
    }

    std::cin >> curstate;
    while (curstate != "END") {
        isterm[curstate] = true;
        std::cin >> curstate;
    }

    auto end = change.end();
    int cnt = 0;

    std::cin >> curstate >> newstate; //start state and input chain
    for (auto i : newstate) {
        auto elem = change.find(std::make_pair(curstate, i));
        if (elem == end) {
            std::cout << 0 << '\n' << cnt << '\n' << curstate << '\n';
            return 0;
        }
        curstate = elem->second;
        cnt++;
    }

    std::cout << isterm[curstate] << '\n' << cnt << '\n' << curstate << '\n';

    return 0;
}
