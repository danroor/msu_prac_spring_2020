#include <iostream>

class Result
{
    uint64_t res;
public:
    Result(uint64_t x) : res(x) {}
    uint64_t get() const { return res; }
};

//calculates func(a,b,k) and returns its result
//via Result exception
void func(uint64_t a, uint64_t b, uint64_t k) {
    if (k == 0) throw Result(a + b);
    if (b == 1) throw Result(a);
    try {
        func(a, b - 1, k);
    } catch(const Result &res1) {
        try {
            func(a, res1.get(), k - 1);
        } catch(const Result &res2) {
            throw Result(res2.get());
        }
    }
}

int main()
{
    uint64_t a, b, k;

    while (std::cin >> a >> b >> k) {
        try {
            func(a, b, k);
        } catch(const Result &res) {
            std::cout << res.get() << std::endl;
        }
    }

    return 0;
}
