#include <vector>
#include <iostream>
#include <algorithm>
#include <cctype>

class FigFactory
{
    FigFactory() {};
    FigFactory(const FigFactory&) = delete;  
    FigFactory& operator=(FigFactory&) = delete;
public:
    static FigFactory& factory_instance() {
        static FigFactory instance;
        return instance;
    }

    Figure *CreateFigure(std::string &s) {
        size_t pos = 0;
        for (; std::isspace(s[pos]); ++pos);

        char type = s[pos];
        s[pos] = ' ';

        switch (type) {
        case 'R':
            return dynamic_cast <Figure *> (Rectangle::make(s));
        case 'S':
            return dynamic_cast <Figure *> (Square::make(s));
        default: //case 'C'
            return dynamic_cast <Figure *> (Circle::make(s));
        }
    }
};

int main()
{
    std::string s;
    std::vector <Figure *> v{};
    auto &factory = FigFactory::factory_instance();

    while (std::getline(std::cin, s)) {
        v.push_back(factory.CreateFigure(s));
    };

    std::stable_sort(v.begin(), v.end(), 

        [](auto x, auto y) {  
            return x->get_square() < y->get_square();
        }
    );

    for (auto &i : v) {
        std::cout << i->to_string() << std::endl;
        delete i;
    }

    return 0;
}
