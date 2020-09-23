#ifndef complex_hpp
#define complex_hpp

#include <iostream>
#include <cmath>
#include <string>

using namespace std;

namespace numbers
{
    class complex
    {
        double x, y;
        
    public:
        complex (double a = 0, double b = 0);
        
        explicit complex (const char *c);
        
        double get_re() const;
        double get_im() const;
        double abs2() const;
        double abs() const;
        
        char* to_string(char *buf, size_t size) const;
        
        complex operator ~() const;
        
        complex operator -() const;
        
        friend complex operator+(const complex &c1, const complex &c2);
        friend complex operator-(const complex &c1, const complex &c2);
        friend complex operator*(const complex &c1 ,const complex &c2);
        friend complex operator/(const complex &c1, const complex &c2);
    };
}

#endif /* complex_hpp */
