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
            switch(tape[i - 1]) {
            case '1':
                state = A;
                //deliberate fall-through
            default:
                i++; //'0', '1', '#'
            }
            break;
        }
        case A: {
            switch(tape[i - 1]) {
            case '1':
                state = S;
                //deliberate fall-through
            case '0':
                i++;
                break;
            default:  //case '#'
                state = B;
                i--;
            }
            break;
        }
        case B: {
            switch(tape[i - 1]) {
            case '0':
            case '1':
                i--;
                break;
            default:   //case '#'
                state = C;
                i++;
            }
            break;
        }
        case C: {
            switch(tape[i - 1]) {
            case '0':
                i++;
                break;
            default: //case '1'
                tape[i - 1] = '0';
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
