#include <iostream>

/*
S aBd
B aBd
B bCc
C bCc
C _
*/

void C(int m)
{
    if (m == 0) {
        return;
    }
    
    std::cout << 'b';
    C(m - 1);
    std::cout << 'c';
}

void B(int n, int m)
{
    if (n == 0) {
        std::cout << 'b';
        C(m - 1);
        std::cout << 'c';
        return;
    }
    
    std::cout << 'a';
    B(n - 1,m);
    std::cout << 'd';
}

void S(int n, int m)
{
    if (n <= 0) {
        return;
    }
    
    std::cout << 'a';
    B(n - 1, m);
    std::cout << 'd' << std::endl;

    S(n - 1, m + 1);
}

int main()
{
    int k;
    std::cin >> k;
    if (k % 2 > 0) {
        return 0;
    }

    S(k / 2 - 1, 1);
       
    return 0;
}
