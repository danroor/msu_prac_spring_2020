#include <vector>
#include <algorithm>

void
process(const std::vector <int> &v1, std::vector <int> &v2) {

    std::vector <int> cpy(v1);
    std::sort(cpy.begin(), cpy.end());
    auto last = std::unique(cpy.begin(), cpy.end());
    cpy.erase(last, cpy.end());

    auto it1 = cpy.begin();
    auto end1 = cpy.end();
    if (it1 == end1) {
        return;
    }
    while (*it1 < 0) {
        ++it1;
        if (it1 == end1) {
            return;
        }
    }

    int sz = v2.size();  
    if (*it1 >= sz) {
        return;
    }

    cpy.erase(cpy.begin(), it1);
    end1 = cpy.end();
    for (it1 = cpy.begin(); it1 != end1 && *it1 < sz; ++it1) {}
    cpy.erase(it1, end1);

    it1 = cpy.begin();
    end1 = cpy.end();
    auto end2 = v2.end();
    auto curswap = v2.begin();
    int cnt = 0;
    for (; cnt != *it1; ++cnt) {
        ++curswap;
    }

    auto it2 = curswap;
    ++it1;
    ++it2;
    ++cnt;
    if (it1 == end1) {
        v2.erase(curswap, it2);
        return;
    }

    for (; it2 != end2; ++it2) {
        if (cnt == *it1) {
            ++it1;
            if (it1 == end1) {
                it1 = cpy.begin();
                *it1 = -1;
            }
        } else {
            std::swap(*curswap, *it2);
            ++curswap;
        }

        ++cnt;
    }

    v2.erase(curswap, end2);
}
