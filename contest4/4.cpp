/*

Написать шаблонную функцию myremove, принимающую две пары итераторов: диапазон элементов,
содержащих номера удаляемых элементов, диапазон элементов, содержащих элементы, подлежащие удалению.
Элементы, подлежащие удалению, в диапазоне нумеруются с нуля.
Номера элементов отражают позиции элементов на момент начала работы программы.
Если номер повторяется более одного раза, все вхождения, кроме первого, игнорируются.
Если номер элемента недопустим, он игнорируется.

Функция возвращает итератор на конец сжатой последовательности во втором контейнере.

Для удаляемых элементов может быть запрещено копирование.


*/

#include <algorithm>
#include <vector>

template <typename iter1, typename iter2>
iter2 myremove(iter1 numbeg, iter1 numend, iter2 rembeg, iter2 remend)
{
    if (numbeg == numend) {
        return remend;
    }

    auto it = numbeg;

    std::vector <int> cpy;
    int sz = std::distance(numbeg, numend);
    cpy.resize(sz);
    for (int i = 0; i < sz; ++i) {
        cpy[i] = *it;
        ++it;
    }
    
    std::sort(cpy.begin(), cpy.end());
    auto last = std::unique(cpy.begin(), cpy.end());
    cpy.erase(last, cpy.end());

    auto it1 = cpy.begin();
    auto end1 = cpy.end();

    while (*it1 < 0) {
        ++it1;
        if (it1 == end1) {
            return remend;
        }
    }

    sz = std::distance(rembeg, remend);  
    if (*it1 >= sz) {
        return remend;
    }

    cpy.erase(cpy.begin(), it1);
    end1 = cpy.end();
    for (it1 = cpy.begin(); it1 != end1 && *it1 < sz; ++it1) {}
    cpy.erase(it1, end1);

    auto beg1 = cpy.begin(); 
    it1 = beg1;
    end1 = cpy.end();
    
    auto curswap = rembeg;
    int cnt = 0;
    for (; cnt != *it1; ++cnt) {
        ++curswap;
    }

    auto it2 = curswap;
    ++it1;
    ++it2;
    ++cnt;
    if (it1 == end1) {
        it1 = beg1;
        *it1 = -1;
    }

    for (; it2 != remend; ++it2) {
        if (cnt == *it1) {
            ++it1;
            if (it1 == end1) {
                it1 = beg1;
                *it1 = -1;
            }
        } else {
            *curswap = std::move(*it2);
            ++curswap;
        }

        ++cnt;
    }

    return curswap;
}
