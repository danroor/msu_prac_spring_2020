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
