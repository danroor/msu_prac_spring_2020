/*

Дан язык L={αβ}, где α={3,4}^n, β={1,2}^m, n >= 0, m >= 0.

На стандартном потоке подаются строки, разделяющиеся пробельными символами.
Для каждой строки на стандартный поток вывода напечатайте 1, если строка принадлежит языку, и 0 в противном случае.


*/


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
