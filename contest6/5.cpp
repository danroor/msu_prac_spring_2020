#include <array>
#include <vector>
#include <complex>
#include <limits>

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
            cplx sqrtD = std::sqrt(b * b - a * c * cplx(4, 0));
            res.push_back((-b - sqrtD) / (a * cplx(2, 0)));
            res.push_back((-b + sqrtD) / (a * cplx(2, 0)));
        }

        return std::pair<bool, vec> (flag, res);
    }
};
