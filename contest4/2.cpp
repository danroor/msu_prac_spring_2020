/*

Напишите шаблонную функцию myfilter, которая принимает объект контейнерного класса и функцию-предикат.
Функция возвращает новый объект того же самого контейнерного класса,
в который скопированы только те объекты исходного контейнерного класса,
которые удовлетворяют заданному предикату.

Стандартными алгоритмами пользоваться запрещено.
*/

#include <functional>

template <typename T>
auto myfilter(const T &cont, std::function <bool (typename T::value_type)> predic) -> T
{
    T newcont;

    for (auto i : cont) {
        if (predic(i)) {
            newcont.insert(newcont.end(), i);
        }
    }

    return newcont;
}
