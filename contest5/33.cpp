#include <cmath>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>

class Figure
{
public:
    virtual ~Figure() {};
    virtual double get_square() const = 0;
    virtual std::string to_string() const = 0;
};

class Rectangle : public Figure
{
    double a, b;
public:
    double get_square() const override {
        return a * b;
    }

    static Rectangle* make(const std::string &s) {
        auto obj = new Rectangle;
        std::stringstream str;
        str << s;
        str >> obj->a >> obj->b;
        return obj;
    }

    std::string to_string() const {
        std::stringstream str;
        std::string s;
        str << "R " << a << " " << b;
        return str.str();
    }
};

class Square : public Figure
{
    double a;
public:
    double get_square() const override {
        return a * a;
    }

    static Square* make(const std::string &s) {
        auto obj = new Square;
        std::stringstream str;
        str << s;
        str >> obj->a;
        return obj;
    }

    std::string to_string() const {
        std::stringstream str;
        std::string s;
        str << "S " << a;
        return str.str();
    }
};

class Circle : public Figure
{
    double r;
public:
    double get_square() const override {
        return M_PI * r * r;
    }

    static Circle* make(const std::string &s) {
        auto obj = new Circle;
        std::stringstream str;
        str << s;
        str >> obj->r;
        return obj;
    }

    std::string to_string() const {
        std::stringstream str;
        std::string s;
        str << "C " << r;
        return str.str();
    }
};

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
        case 'R': {
            auto obj = Rectangle::make(s);
            return dynamic_cast <Figure *> (obj);
            }
        case 'S': {
            auto obj = Square::make(s);
            return dynamic_cast <Figure *> (obj);
            }
        default: { //case 'C'
            auto obj = Circle::make(s);
            return dynamic_cast <Figure *> (obj);
            }
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
