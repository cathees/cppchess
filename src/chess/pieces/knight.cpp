//
// Created by kamui on 12/21/2025.
//

#include "knight.h"

#include <cmath>

bool knight::is_essential() const
{
    return false;
}

bool knight::can_move(int to_row, int to_col, const chessboard& cb) const
{
    int dr = std::abs(to_row - get_row());
    int dc = std::abs(to_col - get_col());

    if (!((dr == 2 && dc == 1) || (dr == 1 && dc == 2)))
        return false;

    const chess_piece* target = cb(to_row, to_col);

    return !target || target->get_color() != get_color();
}

bool knight::controls(int row, int col, const chessboard& cb) const
{
    int dr = std::abs(row - get_row());
    int dc = std::abs(col - get_col());

    return (dr == 2 && dc == 1) || (dr == 1 && dc == 2);
}
