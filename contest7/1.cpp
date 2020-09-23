#include <iostream>

class MyException
{
    std::string s;
public:
    MyException(const std::string &str) : s(str) {}
    ~MyException() {
        std::cout << s << std::endl;
    }
};

void f()
{
    std::string s;
    std::cin >> s;
    if (!s.empty()) {
        try {
            f();
        } catch(...) {}
        throw MyException(s);
    }

    throw 1;
}

int main()
{
    try { f(); } catch(...){}

    return 0;
}
