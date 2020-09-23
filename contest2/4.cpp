#include <cmath>
#include <vector>
#include <iostream>
#include <cstdio>

#include "cmc_complex.h"
#include "cmc_complex_stack.h"
#include "cmc_complex_eval.h"

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
        integral += numbers::eval(func, cur + center) * (cur - prev);
        prev = cur;
    }

    std::cout << integral.to_string() << std::endl;

    return 0;
}
