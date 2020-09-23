#include <iostream>
#include <list>
#include <iterator>
#include <functional>

using namespace std;

template <typename T>
auto myfilter(const T &cont, std::function <bool (typename T::value_type)> predic) -> T
{
    T newcont;

    for (auto i : cont) {
        if (predic(i)) {
            newcont.insert(newcont.end(), i);
        }
    }

    return newcont;
}

int main()
{
    std::list<int> v{1,2,3,4,5,6};

    auto res = myfilter(v, [](int x) { return x % 2 == 1;  } );
   
    for (auto v : res)
        cout << v << endl;
}
