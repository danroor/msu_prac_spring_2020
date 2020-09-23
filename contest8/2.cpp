#include <iostream>
#include <cctype>

enum {
    FirstZeros,
    FirstOnes,
    FurtherZeros,
    FurtherOnes,
    Space,
    NotOK
};

int main()
{
    bool go = true;
    size_t zeros = 0, ones = 0, zcur = 0, ocur = 0;
    char c;

    int state = Space;
    
    while (go) {
        go = bool(std::cin.get(c));

        if (!go || std::isspace(c)) {
            switch(state) {
            case Space:
                break;
            case FirstOnes: {
                std::cout << 1 << std::endl;
                break;
            }
            case FurtherOnes: {
                std::cout << (ocur == ones) << std::endl;
                break;
            }
            default: //NotOK, FirstZeros, FurtherZeros
                std::cout << 0 << std::endl;
            }

            zeros = ones = zcur = ocur = 0;
            state = Space;

        } else if (c == '0') {
            switch(state) {
            case NotOK:
                break;

            case FirstOnes: {
                state = FurtherZeros;
                zcur++;
                break;
            }
            case FurtherOnes: {
                if (ocur != ones) {
                    state = NotOK;
                    break;
                }
                ocur = 0;
                state = FurtherZeros;
                zcur++;
                break;
            }

            case FurtherZeros: {
                zcur++;
                break;
            }
            
            default: { //Space, FirstZeros
                state = FirstZeros;
                zeros++;
            }

            }
        } else if (c == '1') {
            switch(state) {
            case NotOK:
                break;
            case Space: {
                state = NotOK;
                break;
            }
            case FurtherZeros: {
                if (zcur != zeros) {
                    state = NotOK;
                    break;
                }
                zcur = 0;
                state = FurtherOnes;
                ocur++;
                break;
            }
            case FurtherOnes: {
                ocur++;
                break;
            }

            default: { //FirstZeros, FirstOnes
                state = FirstOnes;
                ones++;
            }

            }
        } else {
            state = NotOK;
        }
    }

    return 0;
}
