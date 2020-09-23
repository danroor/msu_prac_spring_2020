#include <limits>
#include <type_traits>
#include <stdexcept>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>



#include <iostream>

using namespace std;

#include "LongLongLong.hpp"

template <class T>
class Range
{
    T low, high;
public:
    Range(T l = T(), T h = T()) : low(l), high(h) {
        static_assert(!std::is_pod<T>::value || 
        (std::is_integral<T>::value && std::is_signed<T>::value ));

        if (l > h) {
            throw std::invalid_argument("");
        }
    }
    explicit Range(const std::string &s) {
        static_assert(!std::is_pod<T>::value || 
        (std::is_integral<T>::value && std::is_signed<T>::value ));

        size_t beg1 = 0, end1 = 0, beg2 = 0, end2 = 0, L = s.length();

        for (size_t i = 0; i < L; ++i) {
            if (!std::isspace(s[i])) {

                if (beg1 > 0 && end1 > 0 && beg2 == 0 ) {
                    beg2 = i;
                }

                if (s[i] == '(') {
                    if (beg1 > 0 || end1 > 0 || beg2 > 0 || end2 > 0) {
                        throw std::invalid_argument("");
                    }
                    beg1 = i + 1;

                } else if (s[i] == ',') {
                    if (beg1 == 0 || end1 > 0) {
                        throw std::invalid_argument("");
                    }
                    end1 = i;

                } else if (s[i] == ')') {
                    if (beg1 == 0 || end1 == 0 || end2 > 0) {
                        throw std::invalid_argument("");
                    }
                    end2 = i;

                } else {
                    if (beg1 == 0 || end2 > 0) {
                        throw std::invalid_argument("");
                    }
                }

            } else if ( !(beg1 > 0 && end1 > 0 && beg2 == 0 ) ) {
                throw std::invalid_argument("");
            }
        }

        if (beg1 == 0 || end1 == 0 || beg2 == 0 || end2 == 0) {
            throw std::invalid_argument("");
        }

        if constexpr (std::is_pod<T>::value) {
            long long l = std::stoll(s.substr(beg1, end1 - beg1));
            long long h = std::stoll(s.substr(beg2, end2 - beg2));

            if (l > h) {
                throw std::invalid_argument("");
            }

            auto minn = std::numeric_limits<T>::min();
            auto maxx = std::numeric_limits<T>::max();

            if (l < minn || l > maxx || h < minn || h > maxx) {
                throw std::range_error("");
            }

            low = l;
            high = h;

        } else {
            low = T(s.substr(beg1, end1 - beg1));
            high = T(s.substr(beg2, end2 - beg2));

            if (low > high) {
                throw std::invalid_argument("");
            }
        }
    }

    std::string to_string() const {
        std::stringstream s;
        if constexpr(std::is_pod<T>::value) {
            s << '(' << static_cast <long long> (low) << ',' << static_cast <long long> (high) << ')';
        } else {
            s << '(' << low << ',' << high << ')';
        }
        return s.str();
    }

    T get_low() const {
        return low;
    }

    T get_high() const {
        return high;
    }

    template <class T1>
    friend Range<T1> operator+(const Range<T1> &r1, const Range<T1> &r2);

    template <class T1>
    friend Range<T1> operator-(const Range<T1> &r1, const Range<T1> &r2);

    template <class T1>
    friend Range<T1> operator*(const Range<T1> &r1, const Range<T1> &r2);

    template <class T1>
    friend Range<T1> operator-(const Range<T1> &r1);
};

template <class T>
Range<T> operator+(const Range<T> &r1, const Range<T> &r2) {
    T x1, x2, x3, x4;

    T l1 = r1.low;
    T h1 = r1.high;
  
    T l2 = r2.low;
    T h2 = r2.high;

    if constexpr(std::is_pod<T>::value) {
        if (__builtin_add_overflow (l1, l2, &x1) ) {
            throw  std::overflow_error("");
        }
        if (__builtin_add_overflow (h1, h2, &x2) ) {
            throw  std::overflow_error("");
        }

        return Range<T>(x1, x2);
            
    } else {
        x1 = l1 + l2;
        x2 = l1 + h2;
        x3 = h1 + l2;
        x4 = h1 + h2;

        return Range<T>(
                std::min( std::min(x1, x2),  std::min(x3, x4) ),
                std::max( std::max(x1, x2),  std::max(x3, x4) ) );
    }
}

template <class T>
Range<T> operator+(const Range<T> &r1, const T &r2) {
    return r1 + Range<T>(r2);
}

template <class T>
Range<T> operator+(const T &r1, const Range<T> &r2) {
    return Range<T>(r1) + r2;
}

template <class T>
Range<T> operator-(const Range<T> &r1, const Range<T> &r2) {
    T x1, x2, x3, x4;

    T l1 = r1.low;
    T h1 = r1.high;
  
    T l2 = r2.low;
    T h2 = r2.high;

    if constexpr(std::is_pod<T>::value) {
        if (__builtin_sub_overflow (l1, h2, &x1) ) {
            throw  std::overflow_error("");
        }
        if (__builtin_sub_overflow (h1, l2, &x2) ) {
            throw  std::overflow_error("");
        }

        return Range<T>(x1, x2);
          
    } else {
        x1 = l1 - l2;
        x2 = l1 - h2;
        x3 = h1 - l2;
        x4 = h1 - h2;

        return Range<T>(
                std::min( std::min(x1, x2),  std::min(x3, x4) ),
                std::max( std::max(x1, x2),  std::max(x3, x4) ) );
    }
}

template <class T>
Range<T> operator-(const Range<T> &r1, const T &r2) {
    return r1 - Range<T>(r2);
}

template <class T>
Range<T> operator-(const T &r1, const Range<T> &r2) {
    return Range<T>(r1) - r2;
}
  
template <class T>
Range<T> operator*(const Range<T> &r1, const Range<T> &r2) {
    T x1, x2, x3, x4;

    T l1 = r1.low;
    T h1 = r1.high;
  
    T l2 = r2.low;
    T h2 = r2.high;

    if constexpr(std::is_pod<T>::value) {
        if (__builtin_mul_overflow (l1, l2, &x1) ) {
            throw  std::overflow_error("");
        }
        if (__builtin_mul_overflow (l1, h2, &x2) ) {
            throw  std::overflow_error("");
        }
        if (__builtin_mul_overflow (h1, l2, &x3) ) {
            throw  std::overflow_error("");
        }
        if (__builtin_mul_overflow (h1, h2, &x4) ) {
            throw  std::overflow_error("");
        }
    } else {
        x1 = l1 * l2;
        x2 = l1 * h2;
        x3 = h1 * l2;
        x4 = h1 * h2;
    }

    return Range<T>(
            std::min( std::min(x1, x2),  std::min(x3, x4) ),
            std::max( std::max(x1, x2),  std::max(x3, x4) ) );
}

template <class T>
Range<T> operator*(const Range<T> &r1, const T &r2) {
    return r1 * Range<T>(r2);
}

template <class T>
Range<T> operator*(const T &r1, const Range<T> &r2) {
    return Range<T>(r1) * r2;
}
    
template <class T>
Range<T> operator-(const Range<T> &r) {
    T l = r.low;
    T h = r.high;

    if ( std::is_pod<T>::value && l == std::numeric_limits<T>::min() ) { 
        throw  std::overflow_error("");
    }

    l = -l;
    h = -h;

    //the definition of unar minus
    //in user-defined class is unknown
    //comparing l to h is necessary
    if (h >= l) {     
        return Range<T>(l, h);
    }

    return Range<T>(h, l);
}

int main()
{
    //cout << (-1 + Range<int>(1,2)).to_string() << endl;


    Range<int> r1(1,2), r2(3,4), r3(-2, 1), r4(-3, -2), r5(-5,-1), r6(0, 4), r7(-4,0);
    Range<signed char> r("(127,127)");
    Range<LongLongLong> rr("(-4,5)");

    cout << r.to_string() << endl << rr.to_string() << endl;

    const Range<int> rrr(-2,3);
/*
        std::cout 
 << std::string("1: ") << (-rrr).to_string() << std::endl
 << std::string("2: ") << (r3-r4).to_string() << std::endl
 << std::string("3: ") << (r1*r2).to_string() << std::endl
 << std::string("4: ") << (r1*r3).to_string() << std::endl
 << std::string("5: ") << (r1*r4).to_string() << std::endl
 << std::string("6: ") << (r3*r4).to_string() << std::endl
 << std::string("7: ") << (r4*r5).to_string() << std::endl
 << std::string("8: ") << (r1*r6).to_string() << std::endl
 << std::string("9: ") << (r1*r7).to_string() << std::endl
 << std::string("10: ") << (r3*r6).to_string() << std::endl
 << std::string("11: ") << (r3*r7).to_string() << std::endl
 << std::string("12: ") << (r4*r6).to_string() << std::endl
 << std::string("13: ") << (r4*r7).to_string() << std::endl
 << std::string("14: ") << (r6*r6).to_string() << std::endl
 << std::string("15: ") << (r6*r7).to_string() << std::endl
 << std::string("16: ") << (r7*r7).to_string() << std::endl;
*/
return 0; }
