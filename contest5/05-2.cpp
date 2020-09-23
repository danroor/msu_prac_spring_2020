#include <cmath>
#include <sstream>

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
    };
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
    };
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
    };
};
