
/*


# 1
Напишите класс Sum таким образом, чтобы конструкция Sum(a, b).get() возвращала сумму двух целых параметров a, b. 
Конструкция Sum(Sum(a,b),c).get() должна возвращать сумму a, b и c.

*/

class Sum
{
    int a, b;    
public:
    Sum(int & x, int & y) : a(x), b(y) {}
    Sum(const Sum & x, int & y) : a(x.a + x.b), b(y) {}
    
    int get() const
    {
        return a + b;
    }
};
