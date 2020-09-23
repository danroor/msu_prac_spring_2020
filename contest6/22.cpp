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
    return dx > dy ? dx : dy;
}

int main()
{
    std::cout << dist(Coord<long long>(5, 4), Coord<long long>(0, 3), Coord<long long>(3, 3)) << std::endl;

    return 0;
}
