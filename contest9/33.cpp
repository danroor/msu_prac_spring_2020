#include <iostream>
#include <string>
#include <>

enum
{
    start,
    shorten,
    non_shorten,
    leftlin,
    rightlin,
    leftauto,
    rightauto,
    lrauto,
    lrlin
};

int main()
{
    std::string left, right;
    int state = start;
    bool s_left_only = true;

    while (std::cin >> left >> right) {
        
        if (right.size() == 1) {
            if (right[0] == '_') {
                if (left[0] == 'S') {
                    switch (state) {
                    case rightlin:
                    case rightauto:
                        state = rightlin;
                        break;
                    case leftlin:
                    case leftauto:
                        state = leftlin;
                        break;
                    case shorten:
                    case non_shorten:
                        break;
                    default: //start, lrlin, lrauto
                        state = lrlin;
                    }
                } else {
                    state = shorten;
                }
            } else if (right[0] >= 'A' && right[0] <= 'Z') {
                switch (state) {
                case rightlin:
                case rightauto:
                    state = rightlin;
                    break;
                case leftlin:
                case leftauto:
                    state = leftlin;
                    break;
                case shorten:
                case non_shorten:
                    break;
                default: //start, lrlin, lrauto
                    state = lrlin;
                }

            } else if (state == start) { //right symbol is a terminal
                state = lrauto;
            }

        } else if (right[0] >= 'A' && right[0] <= 'Z') {
            //left

        } else if (right[sz - 1] >= 'A' && right[sz - 1] <= 'Z') {
            //right


        } else if (state != shorten) {
            state = non_shorten;
        }

        switch (state) {
        case shorten:
            std::cout << 2 << std::endl;
            break;
        case non_shorten:
            std::cout << 21 << std::endl;
            break;
        case leftlin:
            std::cout << 31 << std::endl;
            break;
        case leftauto:
            std::cout << 311 << std::endl;
            break;
        case rightlin:
            std::cout << 32 << std::endl;
            break;
        default: //rightauto
            std::cout << 321 << std::endl;
        }
    }

    return 0;
}
