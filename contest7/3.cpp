#include <iostream>

class S
{
    int x;
    bool stop, not_empty;
public:
    S() {
        stop = !(std::cin >> x);
        not_empty = !stop;
    }
    ~S() {
        if (stop && not_empty)
            std::cout << x << std::endl;
    }
    S(S &&moved) : not_empty(true) {
        stop = !(std::cin >> x);
        if (stop) {
            x = moved.x;
        } else {
            x += moved.x;
        }
        moved.not_empty = moved.stop = false;
    }

    operator bool() const {
        return !stop;
    }
};
