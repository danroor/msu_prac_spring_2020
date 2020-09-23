#include <vector>
#include <iostream>
#include <algorithm>

int
main()
{
    std::vector<double> data{1,2,3,4,5};
    double cur;    

    while (std::cin >> cur) {
        data.push_back(cur);
    }

    int sz = data.size();
    int del = sz / 10;
    auto head = data.begin();
    
    for (int i = 0; i < del; ++i) {
        ++head;
    }
    auto tail = head;

    sz -= del;
    auto tail = data.begin();
    for (int i = del; i < sz; ++i) {
        ++tail;
    }
    ++tail;
    
    sz = data.size();
    del = sz / 10;  

    class sum {
        int summ;
    public:
        sum() : summ(0) {}
        int summa() const { return summ; }
        int operator()(const int &x) {
            summ += x;
        }
    };

    sum s{};
    s = std::for_each(v.begin(), v.end(), s);
    std:: cout << s.summa() << " ";
}
