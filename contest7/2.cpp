/*

Некоторая рекурсивная функция func от трех целых аргументов a, b, k (a, b >= 1, k >= 0)
определена следующим образом:

func(a, b, k) == a + b при k == 0
func(a, b, k) == a при k > 0, b == 1
func(a, b, k) == f(a, f(a, b - 1, k), k - 1) при k > 0, b > 1
На стандартном потоке ввода подаются тройки чисел:
два 64-битных знаковых целых положительных числа a, b и
32-битное целое неотрицательное число k. Для каждой тройки чисел на стандартный поток вывода
напечатайте значение описанной выше функции.

Параметры на входе будут таковы, что вычисление завершится за разумное время.
Для вычислений достаточно 64-битного целого знакового типа.

Для возврата значения из рекурсии используйте исключения.
Выход из рекурсивной функции с помощью явного или неявного return запрещен.

Напишите свой класс (например, Result) для передачи результата вычислений вместе с исключением.
Не используйте выбрасывание исключений базовых (например, int) типов.

В комментарии в начале программы опишите, что из себя представляет эта рекурсивная функция.


*/

#include <iostream>

class Result
{
    uint64_t res;
public:
    Result(uint64_t x) : res(x) {}
    uint64_t get() const { return res; }
};

//calculates func(a,b,k) and returns its result
//via Result exception
void func(uint64_t a, uint64_t b, uint64_t k) {
    if (k == 0) throw Result(a + b);
    if (b == 1) throw Result(a);
    try {
        func(a, b - 1, k);
    } catch(const Result &res1) {
        try {
            func(a, res1.get(), k - 1);
        } catch(const Result &res2) {
            throw Result(res2.get());
        }
    }
}

int main()
{
    uint64_t a, b, k;

    while (std::cin >> a >> b >> k) {
        try {
            func(a, b, k);
        } catch(const Result &res) {
            std::cout << res.get() << std::endl;
        }
    }

    return 0;
}
