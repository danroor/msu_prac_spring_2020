/*

Дано прямоугольное поле размером m строк на n столбцов клеток.
Левая нижняя клетка поля имеет координаты (0,0), правая верхняя клетка поля — (m - 1,n - 1).

Поле закольцовано в тор, то есть склеены верхняя и нижняя границы поля и правая и левая границы поля.

Из некоторой клетки можно перейти за один ход в любую из четырех соседних клеток (если таковые существуют).
Например, из клетки (1,2) можно перейти в клетки (0,2), (2,2), (1,1), (1,3).

Расстояние между двумя клетками — это минимальное число ходов, за которое можно перейти из одной клетки в другую.

На стандартном потоке ввода задаются два целых числа m и n, задающие размеры поля.

Далее вводятся четверки целых чисел r1, c1, r2, c2, задающие координаты (r1,c1) первой и (r2,c2) второй клеток.

Для каждой четверки координат выведите на стандартный поток вывода расстояние между этими клетками.


*/

#include <iostream>

template <typename coord>
class Coord
{
public:
    Coord(coord x = 0, coord y = 0) : row(x), col(y) {}
    coord row, col;
    using value_type = coord;
};

template <class T>
typename T::value_type dist(T field, T cell1, T cell2)
{
    using typ = typename T::value_type;

    typ dx = cell1.row > cell2.row ? cell1.row - cell2.row : cell2.row - cell1.row;
    typ dy = cell1.col > cell2.col ? cell1.col - cell2.col : cell2.col - cell1.col;

    dx = dx < field.row - dx ? dx : field.row - dx;
    dy = dy < field.col - dy ? dy : field.col - dy;
    return dx + dy;
}

int main()
{
    std::cout << dist(Coord(4, 4), Coord(0, 3), Coord(3, 3)) << std::endl;

    return 0;
}
