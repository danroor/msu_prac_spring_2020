#include <iostream>
#include <cassert>
#include <sstream>
#include <vector>

using namespace std;

template <class T>
T f(T x) {
    static_assert(!std::is_pod<T>::value || 
        (std::is_integral<T>::value && std::is_signed<T>::value ) );
    return x;
}

int main() {
    vector<unsigned int> x = {1,2,3};

    int y = 1;
    unsigned int z = 1;

    auto v = f(x);
    y = f(y);
    z = f(z);

    return 0;
}
