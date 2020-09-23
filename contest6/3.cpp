/*

Дано прямоугольное поле из гексагональных элементов (см. рис) размером m строк на n столбцов клеток.
Координаты шестиугольников определяются, как показано на рисунке.

hexagons
Из некоторой клетки можно перейти за один ход в любую из шести соседних клеток.

Расстояние между двумя клетками — это минимальное число ходов,
за которое можно перейти из одной клетки в другую.

В пространстве имен Game напишите шаблонный класс Coord, параметризованный типом координат.
Класс должен содержать открытый тип value_type,
открытые поля row, col и открытый конструктор от 0, 1 или 2 аргументов.

В пространстве имен Game напишите шаблонную функцию dist, принимающую три параметра:
размеры поля, две координаты клеток, которая вычисляет расстояние между двумя клетками.


*/

namespace Game {

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
        typename T::value_type dr, dc;

        dr = cell1.row > cell2.row ? cell1.row - cell2.row : cell2.row - cell1.row;
        dc = cell1.col > cell2.col ? cell1.col - cell2.col : cell2.col - cell1.col;

        if ( (cell1.row > cell2.row ) ^ (cell1.col % 2 == 0)) {
            dr = dr > (dc + 1) / 2 ? dr - (dc + 1) / 2 : 0; 
        } else {
            dr = dr > dc / 2 ? dr - dc / 2 : 0; 
        }
        
        return dr + dc;
       
    }
};
