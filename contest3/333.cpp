#include <vector>
#include <algorithm>
#include <iostream>

void
process(const std::vector <int> &v1, std::vector <int> &v2) {

    std::vector <int> cpy(v1);
    std::sort(cpy.begin(), cpy.end());
    auto last = std::unique(cpy.begin(), cpy.end());
    cpy.erase(last, cpy.end());

    

    auto it = cpy.begin();
    auto end = cpy.end();
    if (it == end) {
        return;
    }
    while (*it < 0) {
        std::cout << "S\n";
        ++it;
        if (it == end) {
            return;
        }
    }

    int sz = v2.size();

    std::vector<bool> flag;
    flag.resize(sz, false);

    auto curfl = flag.begin();
    int cnt = 0;

    for (; it != end; ++it) {
        if (*it >= sz) {
            break;
        }
        for (; cnt < *it; ++cnt) {
            ++curfl;
        }

        *curfl = true;
    }

    end = v2.end();
    auto curdel = v2.begin();

    auto curdelf = flag.begin();
    curfl = curdelf;

    for (it = v2.begin(); it != end; ++it) {
        if (!*curfl) {
            if (curdel != it) {
                std::swap(*curdel, *it);
                std::swap(*curdelf, *curfl);
            }
            ++curdel;
            ++curdelf;
        }

        ++curfl;
    }

    v2.erase(curdel, v2.end());
}

int main()
{
    const std::vector <int> v1 {};
    std::vector <int> v2 {1,2,3};
    process(v1, v2);
    for (auto v : v2) std::cout << v << " ";
}
