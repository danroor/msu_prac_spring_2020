#include <vector>

void
process(std::vector <long long> &v, long long threshold) {

    v.reserve(2 * v.size());

    auto beg = v.rend();

    for (auto i = v.rbegin(); i != beg; ++i) {
        if (*i >= threshold) {
            v.push_back(*i);
        }
    }
}
