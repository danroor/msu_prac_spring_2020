#include "complex.hpp"
using namespace std;

namespace numbers
{
    
    complex::complex (double a, double b): x(a), y(b) {}
    
    complex::complex (const char *c)
    {
        sscanf(c, "(%lf,%lf)", &x, &y);
    }
    
    double complex::get_re() const {
        return x;
    }
    double complex::get_im() const {
        return y;
    }
    double complex::abs2() const {
        return x * x + y * y;
    }
    double complex::abs() const {
        return sqrt(x * x + y * y);
    }
    
    char* complex::to_string(char *buf, size_t size) const {
        snprintf(buf, size, "(%.10g,%.10g)", x, y);
        return buf;
    }
    
    complex complex::operator ~() const {
        return complex(x, -y);
    }
    
    complex complex::operator -() const {
        return complex(-x, -y);
    }
    
    complex operator+(const complex &c1, const complex &c2)
    {
        return complex(c2.x + c1.x, c2.y + c1.y);
    }
    
    complex operator-(const complex &c1, const complex &c2)
    {
        return complex(-c2.x + c1.x, -c2.y + c1.y);
    }
    
    complex operator*(const complex &c1, const complex &c2)
    {
        return complex(c2.x * c1.x - c2.y * c1.y, c2.y * c1.x + c2.x * c1.y);
    }
    
    complex operator/(const complex &c1, const complex &c2)
    {
        return complex((c2.x * c1.x + c2.y * c1.y)/(c2.x * c2.x + c2.y * c2.y),
                       (c2.x * c1.y - c2.y * c1.x)/(c2.x * c2.x + c2.y * c2.y));
    }
    
}
