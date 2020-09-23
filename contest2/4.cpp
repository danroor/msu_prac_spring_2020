/*

# 4
Программе в аргументах командной строки передаются:

Комплексное число C.
Вещественное число R.
Целое число N.
Остальные аргументы - запись функции одного комплексного аргумента в польской записи.
На стандартный поток вывода напечатайте комплексное число I -
результат вычисления криволинейного интеграла по замкнутому контуру - окружности с центром в точке C и радиусом R.

Для вычисления используйте метод прямоугольников. Для этого окружность делится на N частей.

В заголовочном файле cmc_complex.h находится реализация класса numbers::complex,
в заголовочном файле cmc_complex_stack.h находится реализация класса numbers::complex_stack,
в заголовочном файле cmc_complex_eval.h находится реализация функции eval.


*/


#include <cmath>
#include <vector>
#include <iostream>
#include <cstdio>

#include "cmc_complex.h"
#include "cmc_complex_stack.h"
#include "cmc_complex_eval.h"

int main(int argc, char *argv[])
{
    if (argc < 4) {
        return 1;
    }
    
    double cr, ci, r;
    int n;
    sscanf(argv[1], "(%lf,%lf)", &cr, &ci);
    sscanf(argv[2], "%lf", &r);
    sscanf(argv[3], "%d", &n);

    std::vector<std::string> func;

    for (int i = 4; i < argc; ++i) {
        func.push_back(std::string(argv[i]));
    }

    numbers::complex center(cr, ci);
    numbers::complex prev(r, 0);
    numbers::complex cur, integral;

    double angle = 0;
    double turn = 2 * M_PI / n;

    for (int i = 0; i < n; ++i) {
        angle += turn;
        cur = numbers::complex(r * cos(angle), r * sin(angle));
        integral += numbers::eval(func, cur + center) * (cur - prev);
        prev = cur;
    }

    std::cout << integral.to_string() << std::endl;

    return 0;
}
