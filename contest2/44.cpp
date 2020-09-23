#include <iomanip>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <new>
#include <map>
#include <vector>
#include <functional>
#include <iostream>

using namespace std;

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

    class complex_stack
    {
        complex *stack;
        size_t sz, ncur;
    public:
        complex_stack() {
            sz = ncur = 0;
        }

        complex_stack(const complex_stack &oldstack) : sz(oldstack.sz), ncur(oldstack.ncur) {
            stack = new complex[sz];
            //cout << sz << endl;
            for (unsigned int i = 0; i < ncur; ++i) {
                stack[i] = oldstack.stack[i];
                //if (f) cout << ncur << " pisos\n" ;
            }
            //if (f) cout << "pisos\n";
        }

        ~complex_stack() {
            if (sz > 0)
                delete [] stack;
        }

        size_t size() const {
            return ncur;
        }

        complex_stack operator<<(const complex &z) const {
            complex_stack newstack;
            if (ncur == sz) {
                newstack.sz =  (sz << 1) + 1;
                newstack.stack = new complex[newstack.sz];
            } else {
                newstack.sz = sz;
                newstack.stack = new complex[sz];
            }
            newstack.ncur = ncur + 1;
            
            for (int i = 0; i < ncur; ++i) {
                newstack.stack[i] = stack[i];
            }
            newstack.stack[ncur] = z;
            return newstack;
        }

        const complex operator+() const {
            return stack[ncur - 1];
        }

        const complex_stack operator~() const {
            complex_stack newstack(*this);
            //if (f) cout << "pisos\n";
            newstack.ncur--;
            return newstack;
        }

        const complex operator[](const int &i) const {
            return stack[i];
        }

        complex_stack & operator=(const complex_stack &stck) {
            if (sz > 0) {
                delete [] stack;
            }
            sz = stck.sz;
            ncur = stck.ncur;
            stack = new complex[sz];
            
            for (unsigned int i = 0; i < ncur; ++i) {
                new (stack + i) complex(stck.stack[i].re(), stck.stack[i].im());
            }
            return *this;
        }
    };

complex eval(const std::vector<std::string> &args, const complex &z) {
    complex_stack st;

    std::map<std::string, std::function<void()> > ops = {

        {"+", [&st]() {
            complex x = +st;
            st = ~st;
            complex y = +st;
            st = (~st) << y + x;
        } },

        {"-", [&st]() {
            complex x = +st;
            st = ~st;
            complex y = +st;
            st = (~st) << y - x;
        } },

        {"*", [&st]() {
            complex x = +st;
            st = ~st;
            complex y = +st;
            st = (~st) << y * x;
        } },
 
        {"/", [&st]() {
            complex x = +st;
            st = ~st;
            complex y = +st;
            st = (~st) << y / x;
        } },

        {"!", [&st]() {
            complex x = +st;
            st = st << x;
        } },

        {";", [&st]() {
            st = ~st;
        } },
 
        {"~", [&st]() {
            complex x = +st;
            st = ~st;
            st = st << ~x;
        } },
  
        {"#", [&st]() {
            complex x = +st;
            st = ~st;
            st = st << -x;
        } },
    };

    for (auto v : args) {
        switch(v[0]) {
        case '(':
            st = st << complex(v);
            break;
        case 'z':
            st = st << z;
            break;
        default:
            ops.at(v)();
        }
    }

    return +st;
}

};

int main(int argc, char *argv[])
{
    if (argc < 4) {
        return 1;
    }
    
    double cr, ci, r;
    int n;
    sscanf(argv[1], "(%lf,%lf)", &cr, &ci);
    sscanf(argv[2], "%lf", &r);
    sscanf(argv[3], "%d", &n);

    std::vector<std::string> func;

    for (int i = 4; i < argc; ++i) {
        func.push_back(std::string(argv[i]));
    }

    numbers::complex center(cr, ci);
    numbers::complex prev(r, 0);
    numbers::complex cur, integral;

    double angle = 0;
    double turn = 2 * M_PI / n;

    for (int i = 0; i < n; ++i) {
        angle += turn;
        cur = numbers::complex(r * cos(angle), r * sin(angle));
        integral += eval(func, cur + center) * (cur - prev);
        prev = cur;
    }

    std::cout << integral.to_string() << std::endl;

    return 0;
}
