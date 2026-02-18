//
// Created by kamui on 12/21/2025.
//

#include "queen.h"

#include <cmath>


bool queen::is_essential() const
{
    return false;
}

bool queen::can_move(int to_row, int to_col, const chessboard& cb) const
{
    int from_row = get_row();
    int from_col = get_col();

    int dr = to_row - from_row;
    int dc = to_col - from_col;


    if (dr == 0 && dc == 0)
        return false;

    if (dr == 0 || dc == 0) {
        int step_r = (dr == 0) ? 0 : (dr > 0 ? 1 : -1);
        int step_c = (dc == 0) ? 0 : (dc > 0 ? 1 : -1);

        return is_clear_path(to_row, to_col, step_r, step_c, cb) &&
               can_capture_or_move_to(to_row, to_col, cb);
    }

    if (std::abs(dr) == std::abs(dc)) {
        int step_r = (dr > 0) ? 1 : -1;
        int step_c = (dc > 0) ? 1 : -1;

        return is_clear_path(to_row, to_col, step_r, step_c, cb) &&
               can_capture_or_move_to(to_row, to_col, cb);
    }

    return false;
}


bool queen::controls(int r, int c, const chessboard& cb) const
{
    int dr = r - get_row();
    int dc = c - get_col();

    if (dr != 0 && dc != 0 && std::abs(dr) != std::abs(dc))
        return false;

    int step_r = (dr > 0) - (dr < 0);
    int step_c = (dc > 0) - (dc < 0);

    return is_clear_path(r, c, step_r, step_c, cb);
}

