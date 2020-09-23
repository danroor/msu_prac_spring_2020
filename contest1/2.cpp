#include <iostream>

class A
{
    int x;
    bool f;
public:
    A() : f(false) {
        std::cin >> x;
    }
    A(const A & y) : f(true) {
        std::cin >> x;
        x += y.x;
    }
    
    ~A() {
        if (f) {
            std::cout << x << std::endl;
        }
    }
};
