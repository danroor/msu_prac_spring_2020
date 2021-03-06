/*

# 1

В пространстве имен numbers реализуйте класс complex для комплексных чисел над типом double. Класс должен определять:

Конструкторы по умолчанию, от одного и двух аргументов. Должен реализовываться одним конструктором.
Явный (explicit) конструктор из типа std::string, который преобразовывает строку в значение complex.
Строка имеет формат (RE,IM), то есть вещественная и мнимая части (числа типа double) записываются через запятую
в круглых скобках.
Например, строка "(1.0,-5)" определяет комплексное число (1.0,-5.0). Проверка на ошибки не требуется.
Методы re и im для получения вещественной и мнимой части числа.
Метод abs2 для получения квадрата модуля числа.
Метод abs для получения модуля числа.
Метод to_string, который преобразовывает комплексное число в строковое представление (см. выше) и возвращает объект типа
std::string.
Вещественные числа выводятся с 10 значащими цифрами в формате %.10g.
Операции +=, -=, *=, /=.
Операции сложения, вычитания, умножения и деления в обычной инфиксной форме,
которые должны быть определены через соответствующие операции присваивания.
Префиксную операцию ~, которая возвращает новое число, комплексно-сопряженное к аргументу.
Префиксную операцию - смены знака.

*/

#include <iomanip>
#include <string>
#include <cstdio>
#include <cmath>

constexpr int BUF = 50;

namespace numbers {
    class complex
    {
        double r;
        double i;
    public:
        complex(double a = 0.0, double b = 0.0) {
            r = a;
            i = b;
        }
    
        complex(const std::string &str) {
            std::string s = str;
            s[0] = ' ';
            size_t pos = 0;
            r = std::stod(s, &pos);
            for (unsigned int i = 1; i <= pos; ++i) {
                s[i] = ' ';
            }
            i = std::stod(s);
        }
    
        double re() const {
            return r;
        }
    
        double im() const {
            return i;
        }
    
        double abs() const {
            return sqrt(r * r + i * i);
        }
    
        double abs2() const {
            return r * r + i * i;
        }
    
        std::string to_string() const {
            char res[BUF];
            snprintf(res, BUF, "(%.10g,%.10g)", r, i);
            return std::string(res);
        }
    
        complex & operator+=(const complex &z) {
            r += z.r;
            i += z.i;
            return *this;
        }
    
        complex & operator-=(const complex &z) {
            r -= z.r;
            i -= z.i;
            return *this;
        }
    
        complex & operator*=(const complex &z) {
            double rr = r, ii = i;
            r = rr * z.r - ii * z.i;
            i = rr * z.i + ii * z.r;
            return *this;
        }
    
        complex & operator/=(const complex &z) {
            double rr = (r * z.r + i * z.i) / (z.r * z.r + z.i * z.i);
            double ii = (i * z.r - r * z.i) / (z.r * z.r + z.i * z.i);
            r = rr;
            i = ii;
            return *this;
        }
    
        friend const complex operator+(const complex &z1, const complex &z2);
        friend const complex operator-(const complex &z1, const complex &z2);
        friend const complex operator*(const complex &z1, const complex &z2);
        friend const complex operator/(const complex &z1, const complex &z2);

        complex operator~() const {
            return complex(r, -i);
        }
    
        complex operator-() const {
            return complex(-r, -i);
        }
    };

    const complex operator+(const complex &z1, const complex &z2) 
    {
        complex zz(z1.re(), z1.im());
        zz += z2;
        return zz;
    }
 
    const complex operator-(const complex &z1, const complex &z2) 
    {
        complex zz(z1.re(), z1.im());
        zz -= z2;
        return zz;
    }

    const complex operator*(const complex &z1, const complex &z2) 
    {
        complex zz(z1.re(), z1.im());
        zz *= z2;
        return zz;
    }

    const complex operator/(const complex &z1, const complex &z2) 
    {
        complex zz(z1.re(), z1.im());
        zz /= z2;
        return zz;
    }

};
