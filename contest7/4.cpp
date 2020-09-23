/*

Turing machine

(S, '0') → (S, '0', R)
(S, '1') → (A, '1', R)
(S, '#') → (S, '#', S)
(A, '0') → (A, '0', R)
(A, '1') → (S, '1', R)
(A, '#') → (B, '#', L)
(B, '0') → (B, '0', L)
(B, '1') → (B, '1', L)
(B, '#') → (C, '#', R)
(C, '0') → (C, '0', R)
(C, '1') → (D, '0', S)
(D, '0') → (D, '0', S)

*/

#include <iostream>

enum { S, A, B, C, D };

int main()
{

    std::string tape;
    std::cin >> tape;

    int state = S;
    size_t i = 1;
    size_t len = tape.length();
    while (i > 0 && i <= len) {
        switch(state) {
        case S: {
            if (tape[i - 1] == '1') {
                state = A;
            }
            i++;
            break;
        }
        case A: {
            if (tape[i] == '#') {
                state = B;
                i--;
            } else if (tape[i++] == '1') {
                state = S;
            }

            break;
        }
        case B: {
            if (tape[i] == '#') {
                state = C;
                i++;
            } else {
                i--;
            }     

            break;
        }
        case C: {
            switch(tape[i]) {
            case '0':
                i++;
                break;
            default: //case '1'
                tape[i] = '1';
                i = 0;
            }
            break;
        }
        default:  //case D
            //case '0'
            i = 0;
        }
    }

    std::cout << tape << std::endl;

    return 0;
}
