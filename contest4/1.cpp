/*

Напишите функцию-шаблон prоcess от одного параметра-типа: контейнера STL с двунаправленным итератором.
Функция должна вернуть сумму (то есть результат применения operator + или +=) последнего,
третьего с конца и пятого с конца элемента контейнера.
Если в контейнере недостаточно элементов, берутся только существующие.
Если контейнер пуст, результатом будет значение по умолчанию типа элементов.

*/


#include <iterator>

constexpr int step = 2;

template <typename T>
auto process(const T &cont) -> typename T::value_type
{
    size_t sz = cont.size();
    auto begin = std::rbegin(cont);

    if (sz == 0) {
        return typename T::value_type{};
    }
    if (sz < step + 1) {
        return *begin;
    }
    if (sz < 2 * step + 1) {
        return *begin + *std::next(begin, step);
    }

    return *begin + *std::next(begin, step) + 
            *std::next(begin, 2 * step);
}
