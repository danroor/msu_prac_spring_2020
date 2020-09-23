/*

Напишите шаблонную функцию myapply,
которая принимает два итератора на начало и конец обрабатываемой последовательности, и функцию f.
Шаблонная функция myapply применяет заданную функцию ко все элементам в заданном диапазоне итерации.

Напишите функцию myfilter2,
которая принимает два итератора на начало и конец обрабатываемой последовательности, и предикат f.
Функция myfilter2 возвращает вектор ссылок на элементы входной обрабатываемой последовательности,
которые удовлетворяют заданному предикату.

Если к вектору ссылок, который вернула функция myfilter2, применить myapply,
то в случае модификации элементов последовательности в функции, переданной в myapply,
на самом деле изменятся элементы, обрабатываемой последовательности,
переданной при получении вектора ссылок в функцию myfilter2.

Шаблонные функции должны быть применимы к массивам.

Используйте std::reference_wrapper. Стандартными алгоритмами пользоваться запрещено.


*/

#include <vector>
#include <functional>

template <typename iter, typename func>
void myapply(iter begin, iter end, func f)
{
    for (auto it = begin; it != end; ++it) {
        f(*it);
    }
}

template <typename iter, typename func>
auto myfilter2(iter begin, iter end, func predic)
-> std::vector<std::reference_wrapper <typename iter::value_type> >
{
    std::vector<std::reference_wrapper <typename iter::value_type> > newcont;

    for (auto it = begin; it != end; ++it) {
        if (predic(*it)) {
            newcont.push_back(std::ref(*it));
        }
    }

    return newcont;
}

template <typename arr, typename func>
void myapply(arr *begin, arr *end, func f)
{
    for (auto it = begin; it != end; ++it) {
        f(*it);
    }
}

template <typename arr, typename func>
auto myfilter2(arr *begin, arr *end, func predic)
-> std::vector<std::reference_wrapper <arr> >
{
    std::vector<std::reference_wrapper <arr> > newcont;

    for (auto it = begin; it != end; ++it) {
        if (predic(*it)) {
            newcont.push_back(std::ref(*it));
        }
    }

    return newcont;
}
