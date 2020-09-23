/*

Программе на стандартном потоке ввода подаётся последовательность вещественных чисел —
результат серии экспериментов.
Последовательность содержит не менее 10 чисел.
Вычислите и выведите на стандартный поток вывода среднее арифметическое для нормализованной выборки.
Вещественные числа должны быть напечатаны с 10 десятичными знаками после точки.

Нормализованная выборка —
это выборка, у которой отброшены первые и последние 10% измерений (при вычислении 10% дробная часть отбрасывается),
затем у оставшейся выборки отбрасываются 10%
минимальных и максимальных значений
(вычисление 10% ведется от оставшейся после первого отбрасывания части выборки, дробная часть при этом отбрасывается).
Итого, в вычислениях участвует 64% от исходной выборки.

Для вычисления среднего арифметического используйте алгоритм for_each.
Не используйте глобальные переменные.
Не используйте анонимные (lambda) функции.
При нарушении ограничений решения будут дисквалифицированы.

Используйте минимальное число копирований элементов вектора.

Обратите внимание, что алгоритм for_each возвращает в качестве результата класс-функтор,
переданный ему третьим параметром.
Это можно использовать для накопления результата вычисления в классе-функторе.



*/

#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>

int
main()
{
    constexpr int PERCENT = 10, EPS = 10;

    std::vector<double> data;
    double cur;    

    while (std::cin >> cur) {
        data.push_back(cur);
    }

    class NormAndAver {
        double sum;
        int cnt;
    public:
        NormAndAver() : sum(0.0), cnt(0) {}
        double aver() const {
            return sum / cnt;
        }
        void DeletePart(std::vector<double> &v, int percent) const {
            int sz = v.size();
            int del = sz / percent;
 
            auto it = v.begin();
    
            for (int i = 0; i < del; ++i) {
                ++it;
            }
            v.erase(v.begin(), it);

            sz -= 2 * del;
            it = v.begin();
            for (int i = 0; i < sz; ++i) {
                ++it;
            }
            v.erase(it, v.end());
        }
        void operator()(double x) {
            sum += x;
            ++cnt;
        }
    };

    NormAndAver norm_and_aver;
    
    norm_and_aver.DeletePart(data, PERCENT);
    std::sort(data.begin(), data.end());
    norm_and_aver.DeletePart(data, PERCENT);


    NormAndAver res = std::for_each(data.begin(), data.end(), norm_and_aver);
    std::cout << std::setprecision(EPS) << res.aver() << "\n";
}
