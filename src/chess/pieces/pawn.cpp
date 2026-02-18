//
// Created by kamui on 12/22/2025.
//

#include "pawn.h"

#include <cmath>

#include "../chessboard.h"

bool pawn::is_essential() const
{
    return false;
}

bool pawn::can_move(int to_row, int to_col, const chessboard& cb) const
{
    int from_row = get_row();
    int from_col = get_col();

    int dir = (get_color() == piece_color::white) ? -1 : 1;

    int dr = to_row - from_row;
    int dc = to_col - from_col;

    const chess_piece* target = cb(to_row, to_col);

    if (dc == 0) {
        // one square forward
        if (dr == dir && target == nullptr)
            return true;

        int start_row = (get_color() == piece_color::white) ? 6 : 1;
        if (from_row == start_row && dr == 2 * dir) {
            int intermediate_row = from_row + dir;
            if (cb(intermediate_row, from_col) == nullptr &&
                target == nullptr)
                return true;
        }
    }

    if (std::abs(dc) == 1 && dr == dir) {
        if (target != nullptr && target->get_color() != get_color())
            return true;
    }

    return false;
}




bool pawn::controls(int row, int col, const chessboard&) const
{
    int dir = (get_color() == piece_color::white) ? -1 : 1;

    int dr = row - get_row();
    int dc = std::abs(col - get_col());

    return dr == dir && dc == 1;
}

