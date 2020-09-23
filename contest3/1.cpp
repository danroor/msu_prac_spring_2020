#include <vector>

void
process(const std::vector <unsigned long long> &v1, std::vector <unsigned long long> &v2, unsigned int step) {
    
    auto end1 = v1.end();
    auto begin2 = v2.rend();
    auto j = v2.rbegin();
    if (j == begin2) {
        return; 
    }

    auto i = v1.begin();
    while (i != end1) {
        *j += *i;
        ++j;

        for (unsigned int k = 0; k < step; ++k) {
            ++i;
            if (i == end1) {
                j = begin2;
                break;
            }
        }

        if (j == begin2) {
            break;
        }   
    }
}
