//
// Created by kamui on 12/21/2025.
//

#include "rook.h"

bool rook::is_essential() const
{
    return false;
}

bool rook::can_move(int to_row, int to_col, const chessboard& cb) const
{
    int from_row = get_row();
    int from_col = get_col();

    int dr = to_row - from_row;
    int dc = to_col - from_col;

    if (dr == 0 && dc == 0)
        return false;

    if (dr != 0 && dc != 0)
        return false;

    int step_r = (dr == 0) ? 0 : (dr > 0 ? 1 : -1);
    int step_c = (dc == 0) ? 0 : (dc > 0 ? 1 : -1);

    return is_clear_path(to_row, to_col, step_r, step_c, cb) &&
           can_capture_or_move_to(to_row, to_col, cb);
}

bool rook::controls(int r, int c, const chessboard& cb) const
{
    if (r != get_row() && c != get_col())
        return false;

    int dr = (r > get_row()) - (r < get_row());
    int dc = (c > get_col()) - (c < get_col());

    return is_clear_path(r, c, dr, dc, cb);
}
