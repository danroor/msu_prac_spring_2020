/*

Реализуйте класс S следующим образом:

Класс хранит целое число (типа int).
Число считывается со стандартного потока ввода в конструкторе.
Число выводится на стандартный поток вывода в деструкторе.
Следующая программа:
using namespace std;
void func(S v)
{
    if (v) {
        func(move(v));
    }
}

int main()
{
    func(S());
}
считывает последовательность целых чисел и выводит на стандартный поток вывода их сумму.
Если входная последовательность пустая, программа не выводит ничего.
Проверка на переполнение не требуется.

Глобальные переменные, static, mutable запрещены.

Сдаваемый на проверку класс должен подключать необходимые заголовочные файлы.

*/

#include <iostream>

class S
{
    int x;
    bool stop, not_empty;
public:
    S() {
        stop = !(std::cin >> x);
        not_empty = !stop;
    }
    ~S() {
        if (stop && not_empty)
            std::cout << x << std::endl;
    }
    S(S &&moved) : not_empty(true) {
        stop = !(std::cin >> x);
        if (stop) {
            x = moved.x;
        } else {
            x += moved.x;
        }
        moved.not_empty = moved.stop = false;
    }

    operator bool() const {
        return !stop;
    }
};
