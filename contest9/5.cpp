/*

На вход подается описание КС-грамматики в следующем формате:

<левая часть> <правая часть>

где <...> – строки, состоящие из цифр, строчных и заглавных латинских символов,
а также символа ‘_’, означающего пустую цепочку (эпсилон).

Строчные символы и цифры – терминальные (из Т).
Заглавные – нетерминальные (из N).
Правила грамматики задаются не в сокращенной форме.

На выходе программа должна вывести:
правила эквивалентной грамматики без недостижимых символов не в сокращенной форме.

Пример

Вход
S a
S Bc
D e

Выход
S a
S Bc

*/

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
