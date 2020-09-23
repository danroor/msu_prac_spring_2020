#include <vector>
#include <functional>

template <typename iter, typename func>
void myapply(iter begin, iter end, func f)
{
    for (auto it = begin; it != end; ++it) {
        f(*it);
    }
}

template <typename iter, typename func>
auto myfilter2(iter begin, iter end, func predic)
-> std::vector<std::reference_wrapper <typename iter::value_type> >
{
    std::vector<std::reference_wrapper <typename iter::value_type> > newcont;

    for (auto it = begin; it != end; ++it) {
        if (predic(*it)) {
            newcont.push_back(std::ref(*it));
        }
    }

    return newcont;
}

template <typename arr, typename func>
void myapply(arr *begin, arr *end, func f)
{
    for (auto it = begin; it != end; ++it) {
        f(*it);
    }
}

template <typename arr, typename func>
auto myfilter2(arr *begin, arr *end, func predic)
-> std::vector<std::reference_wrapper <arr> >
{
    std::vector<std::reference_wrapper <arr> > newcont;

    for (auto it = begin; it != end; ++it) {
        if (predic(*it)) {
            newcont.push_back(std::ref(*it));
        }
    }

    return newcont;
}
