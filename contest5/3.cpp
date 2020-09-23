/*

Даны классы Figure, Rectangle, Square, Circle (см. предыдущие задачи).

Дополнительно для всех фигур определен метод to_string,
который возвращает строку std::string, описывающую данную фигуру.

Для класса Rectangle строка имеет вид

R WIDTH HEIGHT
Для класса Square строка имеет вид

S SIZE
Для класса Circle строка имеет вид

C RADUIS
Где WIDTH, HEIGHT, SIZE, RADUIS — соответствующие параметры фигуры.

Напишите программу. На стандартном потоке ввода подаются описания фигур,
строго по одной фигуре на строку текста. Строка описания фигуры имеет вид

TYPE PARAMS
Где TYPE — это R, S или C обозначающие соответствующие фигуры.
PARAMS — это параметры создания фигуры, без изменения передаваемые в функцию make.
Элементы в строке могут разделяться произвольным количеством пробельных символов.

На стандартный поток вывода выведите фигуры,
отсортированные в порядке возрастания площади фигур.
Если несколько фигур имеют равную площадь, сохраняется их относительный порядок из входных данных.

Указания

Не используйте глобальные переменные!

Для чтения строки текста из входного потока используйте std::getline.

Для покомпонентного чтения из строки можете использовать std::istringstream (опционально).

Для хранения фигур используйте std::vector. Для стабильной сортировки используйте stable_sort.

Не забывайте корректно освобождать всю динамическую память.

Реализуйте класс-фабрику классов для порождения объектов фигур.
Фабрика классов должна быть синглтоном.
Экземпляр синглтона должен возвращаться статической функцией factory_instance.

Дополнительно:

Для автоматического освобождения памяти можете использовать std::unique_ptr.

Чтобы не использовать if для проверки типа,
реализуйте фабрику классов на основе std::map и std::function.

*/

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
