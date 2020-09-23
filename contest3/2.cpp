#include <vector>

void
process(std::vector <long long> &v, long long threshold) {
    unsigned int cnt = 0;
    auto beg = v.rend();

    for (auto i = v.rbegin(); i != beg; ++i) {
        if (*i >= threshold) {
            ++cnt;
        }
    }

    if (cnt == 0) {
        return;
    }

    v.reserve(v.size() + cnt);
    beg = v.rend();

    for (auto i = v.rbegin(); i != beg; ++i) {
        if (*i >= threshold) {
            v.push_back(*i);
        }
    }
}
