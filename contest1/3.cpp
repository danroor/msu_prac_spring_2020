/*

# 3
Напишите класс Sub таким образом, чтобы для двух целых параметров (типа int) a, b конструкция Sub(a, b).value() возвращала разность a, b. 
Конструкция Sub(Sub(a,b),c).value() должна возвращать разность a − b − c.

В классе Sub должно быть определено не более трёх конструкторов.

*/


class Sub
{
    int a, b;
public:    
    Sub(const int & x, const int & y) : a(x), b(y) {}
    Sub(const Sub & x, const int & y) : a(x.a - x.b), b(y) {}
    Sub(const int & x, const Sub & y) : a(x), b(y.a - y.b) {}
        
    int value() const
    {
        return a - b;
    }
};
