#include <array>
#include <vector>
#include <complex>
//#include <utility>
#include <limits>
#include <iostream>
namespace Equations {
    template <class T>
    std::pair <bool, std::vector <std::complex <T> > > 
            quadratic(std::array <std::complex <T>, 3 > v)
    {
        using cplx = std::complex <T>;
        using vec = std::vector<cplx>;

        T zero = 32 * std::numeric_limits<T>::epsilon();
        cplx a = v[2], b = v[1], c = v[0];
        bool flag = true;
        vec res;

        if (std::norm(a) < zero) {
        //linear
            if (std::norm(b) < zero) {
                if (std::norm(c) < zero) {
                    flag = false;
                } //else no roots, res is empty
            } else {
                res.push_back(-c / b);
            }
        } else {
        //quadratic
            cplx sqrtD = std::sqrt(b * b - a * c * 4.0);
            res.push_back((-b - sqrtD) / (c * 2.0));
            res.push_back((-b + sqrtD) / (c * 2.0));
        }

        return std::pair<bool, vec> (flag, res);
    }
};

int main()
{
    using namespace std::complex_literals;

    std::array<std::complex <double>,3> v1{ 1.0, 0.0, 0 };

    auto [res, v2] = Equations::quadratic(v1);
    std::cout << res << std::endl;

    for (auto i : v2) std::cout << i << std::endl;

    return 0;
}
