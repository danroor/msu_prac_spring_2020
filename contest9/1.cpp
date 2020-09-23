/*
Язык:
L = { a^n 0^m b^n 1^m | n,m > 0 }

Язык типа 1, неукорачивающая грамматика:

S -> XY
X -> AB | AXB
Y -> OT | OYI
TI -> IT
BO -> OB
A -> aC
CA ->aC
CO -> 0D
DO -> 0D
DB -> bE
EB -> bF
FI -> 1F
FT -> 1G
G -> 1

*/

#include <iostream>
#include <string>

enum { A, B, O, I };

int main()
{
    bool ok;
    int ca, cb, c0, c1, state;

    std::string s;
    while (std::cin >> s) {
        ok = true;
        ca = cb = c0 = c1 = 0;
        state = A;

        for (char i : s) {
            switch(state) {
            case A:
                switch(i) {
                case 'a':
                    ca++;
                    break;
                case '0':
                    ok = ca > 0;
                    state = O;
                    c0++;
                    break;
                default: //1,b, other symbols
                    ok = false;
                }

                break;
            case O:
                switch(i) {
                case '0':
                    c0++;
                    break;
                case 'b':
                    state = B;
                    cb++;
                    break;
                default:
                    ok = false;
                }

                break;
            case B:
                switch(i) {
                case 'b':
                    cb++;
                    break;
                case '1':
                    ok = ca == cb;
                    state = I;
                    c1++;
                    break;
                default:
                    ok = false;
                }

                break;
            default: //case I:
                if (i == '1') {
                    c1++;
                } else {
                    ok = false;
                }
            }

            if (!ok) {
                break;
            }
        }

        std::cout << (ok && ca == cb && c0 == c1) << std::endl;
    }

    return 0;
}
