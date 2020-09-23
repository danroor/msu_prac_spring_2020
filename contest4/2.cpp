#include <functional>

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
