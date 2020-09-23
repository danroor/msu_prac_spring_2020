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
