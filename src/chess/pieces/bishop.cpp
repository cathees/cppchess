//
// Created by kamui on 12/21/2025.
//

#include "bishop.h"

#include <cmath>

#include "../chessboard.h"

bool bishop::is_essential() const
{
    return false;
}

bool bishop::can_move(int to_row, int to_col, const chessboard& cb) const
{
    int from_row = get_row();
    int from_col = get_col();

    int dr = to_row - from_row;
    int dc = to_col - from_col;

    if (std::abs(dr) != std::abs(dc))
        return false;

    int step_r = (dr > 0) ? 1 : -1;
    int step_c = (dc > 0) ? 1 : -1;

    int r = from_row + step_r;
    int c = from_col + step_c;

    while (r != to_row && c != to_col) {
        if (cb(r, c) != nullptr)
            return false;
        r += step_r;
        c += step_c;
    }

    const chess_piece* target = cb(to_row, to_col);
    return !target || target->get_color() != get_color();
}

bool bishop::controls(int r, int c, const chessboard& cb) const
{
    if (std::abs(r - get_row()) != std::abs(c - get_col()))
        return false;

    int dr = (r > get_row()) - (r < get_row());
    int dc = (c > get_col()) - (c < get_col());

    return is_clear_path(r, c, dr, dc, cb);
}
