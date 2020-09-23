#include <iostream>
#include <iomanip>
#include <cmath>

constexpr int EPS = 10;

int main()
{
    int cnt = 0;
    double aver = 0, avsqr = 0, cur;
    
    while (std::cin >> cur) {
        aver += cur;
        avsqr += cur * cur;
        cnt++;
    }
    
    std::cout << std::setprecision(EPS) << aver / cnt << std::endl;
    aver = aver / cnt;
    aver *= aver;
    std::cout << std::setprecision(EPS) << sqrt(avsqr / cnt - aver) << std::endl;
    
    return 0;
}
