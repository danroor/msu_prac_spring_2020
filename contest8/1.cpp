#include <iostream>

int main()
{
    bool flag, ok;

    std::string s;
    while (std::cin >> s) {
        flag = ok = true;
        for (auto i : s) {
            if (i == '3' || i == '4') {
                if (!flag) {
                    ok = false;
                    break;
                }
            } else if (i == '1' || i == '2') {
                flag = false;
            } else {
                ok = false;
                break;
            }
        }
        std::cout << ok << std::endl;
    }
}
