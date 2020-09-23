#include <vector>
#include <functional>
#include <map>

namespace numbers {
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
}
