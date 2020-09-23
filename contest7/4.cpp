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
