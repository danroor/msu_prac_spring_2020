#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>

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
    
        complex(std::string s) {
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
            std::ostringstream strm;
            strm << std::fixed << '(' << std::setprecision(10) << r << ',' << i << ')';
            return strm.str();
        }
    
        complex & operator+=(complex z) {
            r += z.r;
            i += z.i;
            return *this;
        }
    
        complex & operator-=(complex z) {
            r -= z.r;
            i -= z.i;
            return *this;
        }
    
        complex & operator*=(complex z) {
            double rr = r, ii = i;
            r = rr * z.r - ii * z.i;
            i = rr * z.i + ii * z.r;
            return *this;
        }
    
        complex & operator/=(complex z) {
            double rr = (r * z.r + i * z.i) / (z.r * z.r + z.i * z.i);
            double ii = (i * z.r - r * z.i) / (z.r * z.r + z.i * z.i);
            r = rr;
            i = ii;
            return *this;
        }
    
        complex operator+(complex z) const {
            complex zz(r, i);
            zz += z;
            return zz;
        }
    
        complex operator-(complex z) const {
            complex zz(r, i);
            zz -= z;
            return zz;
        }
    
        complex operator*(complex z) const {
            complex zz(r, i);
            zz *= z;
            return zz;
        }
    
        complex operator/(complex z) const {
            complex zz(r, i);
            zz /= z;
            return zz;
        }
    
        complex operator~() const {
            return complex(r, -i);
        }
    
        complex operator-() const {
            return complex(-r, -i);
        }
    };
};
