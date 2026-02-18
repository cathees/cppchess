
#include "king.h"

#include <cmath>

#include "rook.h"
#include "../chessboard.h"

bool king::is_essential() const
{
    return true;
}

bool king::can_move(int to_row, int to_col, const chessboard& cb) const
{
    int from_row = get_row();
    int from_col = get_col();

    int dr = to_row - from_row;
    int dc = to_col - from_col;

    // normal king move
    if (std::abs(dr) <= 1 && std::abs(dc) <= 1 && !(dr == 0 && dc == 0)) {
        const chess_piece* target = cb(to_row, to_col);
        return !target || target->get_color() != get_color();
    }

    if (dr == 0 && std::abs(dc) == 2 && !has_moved) {
        int rook_col = (dc > 0) ? cb.get_size() - 1 : 0;
        int step = (dc > 0) ? 1 : -1;

        const chess_piece* rookp = cb(from_row, rook_col);
        if (!rookp || rookp->get_color() != get_color())
            return false;

        const auto* r = dynamic_cast<const rook*>(rookp);
        if (!r || r->get_color() != get_color())
            return false;

        for (int c = from_col + step; c != rook_col; c += step)
            if (cb(from_row, c) != nullptr)
                return false;

        return true;
    }

    return false;
}



bool king::controls(int row, int col, const chessboard&) const
{
    int dr = std::abs(row - get_row());
    int dc = std::abs(col - get_col());

    return dr <= 1 && dc <= 1 && !(dr == 0 && dc == 0);
}

