#include <vector>
#include <iostream>

using namespace std;

void
process(std::vector <long long> &v, long long threshold) {
    unsigned int cnt = 0;
    auto beg = v.rend();

    for (auto i = v.rbegin(); i != beg; ++i) {
        if (*i >= threshold) {
            ++cnt;
        }
    }

    v.reserve(v.size() + cnt);
    beg = v.rend();

    for (auto i = v.rbegin(); i != beg; ++i) {
        if (*i >= threshold) {
            v.push_back(*i);
        }
    }
}

int main()
{
    std::vector <long long> v{1,3,5,2,4,7,3,5,1,5,-4};
    process(v, 4);
    for (auto v : v) std::cout << v << " ";
}
