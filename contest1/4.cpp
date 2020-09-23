/*

# 4
На стандартном потоке ввода задаётся непустая последовательность вещественных чисел.

На стандартный поток вывода напечатайте среднее значение элементов последовательности и среднее квадратичное отклонение. Числа выводите с 10 знаками после десятичной точки.

Используйте средства ввода-вывода языка Си++. Для вывода числа используйте setprecision.

Не храните введенную последовательность чисел в памяти, то есть не используйте vector, list и т. п.


*/


#include <iostream>
#include <iomanip>
#include <cmath>

constexpr int EPS = 10;

int main()
{
    int cnt = 0;
    double aver = 0, avsqr = 0, cur;
    
    while (std::cin >> cur) {
        aver += cur;
        avsqr += cur * cur;
        cnt++;
    }
    
    std::cout << std::setprecision(EPS) << aver / cnt << std::endl;
    aver = aver / cnt;
    aver *= aver;
    std::cout << std::setprecision(EPS) << sqrt(avsqr / cnt - aver) << std::endl;
    
    return 0;
}
