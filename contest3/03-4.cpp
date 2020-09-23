#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>

int
main()
{
    constexpr int PERCENT = 10, EPS = 10;

    std::vector<double> data;
    double cur;    

    while (std::cin >> cur) {
        data.push_back(cur);
    }

    class NormAndAver {
        double sum;
        int cnt;
    public:
        NormAndAver() : sum(0.0), cnt(0) {}
        double aver() const {
            return sum / cnt;
        }
        void DeletePart(std::vector<double> &v, int percent) const {
            int sz = v.size();
            int del = sz / percent;
 
            auto it = v.begin();
    
            for (int i = 0; i < del; ++i) {
                ++it;
            }
            v.erase(v.begin(), it);

            sz -= 2 * del;
            it = v.begin();
            for (int i = 0; i < sz; ++i) {
                ++it;
            }
            v.erase(it, v.end());
        }
        void operator()(double x) {
            sum += x;
            ++cnt;
        }
    };

    NormAndAver norm_and_aver;
    
    norm_and_aver.DeletePart(data, PERCENT);
    std::sort(data.begin(), data.end());
    norm_and_aver.DeletePart(data, PERCENT);


    NormAndAver res = std::for_each(data.begin(), data.end(), norm_and_aver);
    std::cout << std::setprecision(EPS) << res.aver() << "\n";
}
