/*

В пространстве имен Equations определите шаблонную функцию quadratic,
решающую уравнение az2+bz+c=0 в поле комплексных чисел над любым вещественным типом,
поддерживаемым в заголовочном файле <complex>.
Функция принимает массив (std::array) v из трех
элементов комплексных коэффициентов уравнения (c - v[0], b - v[1], a - v[2]),
функция возвращает пару std::pair из булевского значения и вектора корней.
Булевское значение (first) равно false, если корней уравнения бесконечно много.
В противном случае first равно true и в векторе second возвращается вектор корней,
содержащий 0 элементов, если корней нет; 1 элемент,
если уравнение имеет один корень (то есть линейное);
2 элемента, если уравнение имеет два корня (возможно, равные).

Если на вход передается массив (std::array) другого размера или
массив не комплексных чисел - поведение функции не определено.

*/

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
