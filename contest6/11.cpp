#include <iostream>
#include <list>
#include <iterator>

using namespace std;

constexpr int step = 2;

template <typename T>
auto process(const T &cont) -> typename T::value_type
{
    size_t sz = cont.size();
    auto begin = std::rbegin(cont);

    if (sz == 0) {
        return typename T::value_type{};
    }
    if (sz < step + 1) {
        return *begin;
    }
    if (sz < 2 * step + 1) {
        return *begin + *std::next(begin, step);
    }

    return *begin + *std::next(begin, step) + 
            *std::next(begin, 2 * step);
}

int main()
{
    std::list<int> v{};

    int res = process(v);
    cout << res << endl;
}
