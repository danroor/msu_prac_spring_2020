#include <iostream>
#include <string>
#include <map>
#include <utility>

// L = { ab, a from {0,1}^*, b from { 100, 101, 110, 111 } }

enum
{
    S,                //start
    E1, E2, E3, E4,   //ends
    A, B, C, D
};

int main()
{
    std::string s;
    int state;

    std::map < std::pair <int, char> , int> change;
    change[std::make_pair(S, '0')] = A;
    change[std::make_pair(S, '1')] = B;

    change[std::make_pair(A, '0')] = A;
    change[std::make_pair(A, '1')] = B;

    change[std::make_pair(B, '0')] = C;
    change[std::make_pair(B, '1')] = D;

    change[std::make_pair(C, '0')] = E1;
    change[std::make_pair(C, '1')] = E2;

    change[std::make_pair(D, '0')] = E3;
    change[std::make_pair(D, '1')] = E4;

    change[std::make_pair(E1, '0')] = A;
    change[std::make_pair(E1, '1')] = B;

    change[std::make_pair(E2, '0')] = C;
    change[std::make_pair(E2, '1')] = D;

    change[std::make_pair(E3, '0')] = E1;
    change[std::make_pair(E3, '1')] = E2;

    change[std::make_pair(E4, '0')] = E3;
    change[std::make_pair(E4, '1')] = E4;

    while (std::cin >> s) {
        state = S;
        for (auto i : s) {
            if (i != '0' && i != '1') {
                state = S;
                break;
            }

            state = change[std::make_pair(state, i)];
        }

        std::cout << (state == E1 || state == E2 || state == E3 || state == E4) << std::endl;
    }

    return 0;
}
