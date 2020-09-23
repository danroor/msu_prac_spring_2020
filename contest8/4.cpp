/*

Напишите шаблонный класс Range, который реализует поддержку диапазонов любых знаковых целых чисел.

Класс должен иметь поля low и high,
класс представляет целые значения в диапазоне [low,high] (границы включены).

Определите конструктор по умолчанию, от одного и двух целых аргументов.
Недостающие аргументы равны значению по умолчанию.
Если нарушено условие low <= high, должно выбрасываться исключение std::invalid_argument.

Определите явный (explicit) конструктор из строки std::string,
который преобразует строку в формате (LOW,HIGH) в значение класса,
где LOW, HIGH — значения типа носителя, причем low <= high.
В случае ошибки преобразования должно выбрасываться исключение std::invalid_argument.
В случае ошибки переполнения должно выбрасываться исключение std::range_error.
Пробельные символы в формате отсутствуют. (но это не точно)

Определите метод to_string для преобразования в строку std::string,
который использует формат преобразования, описанный выше.

Определите методы get_low, get_high.

Определите бинарные операции +, - и * и унарную операцию -.
Результатом операций является новый диапазон,
являющийся диапазоном наименьшей длины,
в который гарантированно попадают результаты выполнения соответствующей операции
над произвольными числами исходных диапазонов. Например, (1,2) + (-3, 4) == (-2, 6).

Если типом шаблона является знаковый стандартный тип (signed char, ..., long long),
при выполнении операций должно контролироваться переполнение.
В случае обнаружения переполнения должно выбрасываться исключение std::overflow_error.
Если типом шаблона является пользовательский тип, контроль переполнения возлагается на него.

Если типом шаблона является пользовательский тип,
для него должны быть определены все операции,
позволяющие использовать его вместо стандартного целого типа (в контексте реализации Range).
Кроме того, для него должен быть определен явный конструктор преобразования из std::string,
и операция вывода в поток.
Вам не нужно реализовывать такой пользовательский тип,
но класс Range будет тестироваться с таким пользовательским типом.

Если типом шаблона не является ни пользовательский,
ни стандартный знаковый тип программа не должна компилироваться.

Вспомогательные сущности (шаблоны, функции, классы, ...) поместите в отдельное пространство имен RangeImpl,
чтобы они не "засоряли" глобальное пространство имен.

*/


#include <limits>
#include <type_traits>
#include <stdexcept>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

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
        throw std::overflow_error("");
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
