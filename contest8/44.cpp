#include <limits>
#include <type_traits>
#include <stdexcept>
#include <string>
#include <sstream>
#include <functional>
#include <utility>

#include <iostream>

class LongLongLong
{
    int a_;
public:
    LongLongLong(int a = 0): a_(a) {
    }
    LongLongLong(std::string str) {
        std::cout << "LongLongLong c-tor: str = \'";
        std::cout << str << "'\n";
        std::istringstream(str) >> a_;
    }
    int get() const {
        return a_;
    }
    friend std::ostream& operator << (std::ostream& out, LongLongLong var) {
        out << var.a_;
        return out;
    }
    LongLongLong& operator-() {
        a_ = -a_;
        return *this;
    }
};

bool operator< (LongLongLong left, LongLongLong right) {
    return left.get() < right.get();
}

bool operator> (LongLongLong left, LongLongLong right) {
    return left.get() > right.get();
}

LongLongLong operator+(LongLongLong left, LongLongLong right) {
    return LongLongLong(left.get() + right.get());
}

LongLongLong operator-(LongLongLong left, LongLongLong right) {
    return LongLongLong(left.get() - right.get());
}

LongLongLong operator*(LongLongLong left, LongLongLong right) {
    return LongLongLong(left.get() * right.get());
}

namespace RangeImpl
{
    template <class T>
    T min(T first, T second) {
        return first < second ? first : second;
    }

    template <class T>
    T max(T first, T second) {
        return first > second ? first : second;
    }

    template<class T, bool flag>
    class RangeImp{};

    template <class T>
    class RangeImp<T, true>
    {
        T low, high;
    public:
        RangeImp(T l = T(), T h = T() ) : low(l), high(h) {
            if (l > h) {
                throw std::invalid_argument("");
            }
        }

        T get_low() const {
            return low;
        }

        T get_high() const {
            return high;
        }

        explicit RangeImp(const std::string &str) {
            std::string s(str);
            s[0] = ' ';
            size_t pos = 0;

            long long l = std::stoll(s, &pos);
            for (unsigned int i = 1; i <= pos; ++i) {
                s[i] = ' ';
            }
            long long h = std::stoll(s);

            if (l > h) {
                throw std::invalid_argument("");
            }
            if (l < std::numeric_limits<T>::min() || l > std::numeric_limits<T>::max() ||
                    h < std::numeric_limits<T>::min() || h > std::numeric_limits<T>::max()) {
                throw std::range_error("");
            }

            low = l;
            high = h;
        }

        std::pair<T, T> unar_minus() {
            T l = low;
            T h = high;

            if ( std::is_pod<T>::value && l == std::numeric_limits<T>::min() ) { 
                throw  std::overflow_error("");
            }

            l = -l;
            h = -h;

            //the definition of unar minus
            //in user-defined class is unknown
            //comparing l to h is necessary
            if (h > l) {     
                return std::make_pair(l, h);
            }

            return std::make_pair(h, l);
        }

        std::pair<T, T> add(const RangeImp<T, true> &r2) {
            T x1, x2, x3, x4;

            T l1 = low;
            T h1 = high;
  
            T l2 = r2.low;
            T h2 = r2.high;

            if constexpr(std::is_pod<T>::value) {
                if (__builtin_add_overflow (l1, l2, &x1) ) {
                    throw  std::overflow_error("");
                }
                if (__builtin_add_overflow (h1, h2, &x2) ) {
                    throw  std::overflow_error("");
                }

                return std::make_pair(x1, x2);
            
            } else {
                x1 = l1 + l2;
                x2 = l1 + h2;
                x3 = h1 + l2;
                x4 = h1 + h2;

                return std::make_pair(
                        RangeImpl::min( RangeImpl::min(std::ref(x1), std::ref(x2)), 
                        RangeImpl::min(std::ref(x3), std::ref(x4))),
                        RangeImpl::max( RangeImpl::max(std::ref(x1), std::ref(x2)),
                        RangeImpl::max(std::ref(x3), std::ref(x4))));
            }
        }
 
        std::pair<T, T> sub(const RangeImp<T, true> &r2) {
            T x1, x2, x3, x4;

            T l1 = low;
            T h1 = high;
  
            T l2 = r2.low;
            T h2 = r2.high;

            if constexpr(std::is_pod<T>::value) {
                if (__builtin_sub_overflow (l1, h2, &x1) ) {
                    throw  std::overflow_error("");
                }
                if (__builtin_sub_overflow (h1, l2, &x2) ) {
                    throw  std::overflow_error("");
                }

                return std::make_pair(x1, x2);
            
            } else {
                x1 = l1 - l2;
                x2 = l1 - h2;
                x3 = h1 - l2;
                x4 = h1 - h2;

                return std::make_pair(
                        RangeImpl::min( RangeImpl::min(std::ref(x1), std::ref(x2)), 
                        RangeImpl::min(std::ref(x3), std::ref(x4))),
                        RangeImpl::max( RangeImpl::max(std::ref(x1), std::ref(x2)),
                        RangeImpl::max(std::ref(x3), std::ref(x4))));
            }
        }

        std::pair<T, T> mul(const RangeImp<T, true> &r2) {
            T x1, x2, x3, x4;

            T l1 = low;
            T h1 = high;
  
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

            return std::make_pair(
                    RangeImpl::min( RangeImpl::min(std::ref(x1), std::ref(x2)), 
                    RangeImpl::min(std::ref(x3), std::ref(x4))),
                    RangeImpl::max( RangeImpl::max(std::ref(x1), std::ref(x2)),
                    RangeImpl::max(std::ref(x3), std::ref(x4))));
        }

    };
};


template <class T, bool f = !std::is_pod<T>::value || 
        (std::is_integral<T>::value && std::is_signed<T>::value ) >
class Range
{
    using Impl = RangeImpl::RangeImp<T,f>;
    Impl *ptr;
public:
    Range(T l = T(), T h = T()) : ptr(new Impl(l, h) ) {}
    explicit Range(const std::string &s) : ptr(new Impl(s) ) {}
    ~Range() {
        delete ptr;
    }

    std::string to_string() const {
        std::stringstream s;
        s << '(' << ptr->get_low() << ',' << ptr->get_high() << ')';
        return s.str();
    }

    T get_low() const {
        return ptr->get_low();
    }

    T get_high() const {
        return ptr->get_high();
    }

    Range<T, f> operator+(const Range<T, f> &r2) {
        auto borders = ptr->add( *(r2.ptr) );
        return Range<T, f>(borders.first, borders.second);
    }
    
    Range<T, f> operator-(const Range<T, f> &r2) {
        auto borders = ptr->sub( *(r2.ptr) );
        return Range<T, f>(borders.first, borders.second);
    }

    Range<T, f> operator*(const Range<T, f> &r2) {
        auto borders = ptr->mul( *(r2.ptr) );
        return Range<T, f>(borders.first, borders.second);
    }

    Range<T, f> operator-() {
        auto borders = ptr->unar_minus();
        return Range<T, f>(borders.first, borders.second);
    }
};

int main()
{
    Range<int> r1(-2147483647), r2(-1);
    Range<LongLongLong> r(1,3), rr(4,5);

        std::cout 
 << std::string("1: ") << (r+rr).to_string() << std::endl; 

}
