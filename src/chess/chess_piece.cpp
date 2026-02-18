#include "chess_piece.h"
#include "chessboard.h"

bool chess_piece::is_clear_path(int to_row, int to_col,
                                int step_row, int step_col,
                                const chessboard& cb) const
{
    int r = get_row() + step_row;
    int c = get_col() + step_col;

    while (r != to_row || c != to_col) {
        if (cb(r, c) != nullptr)
            return false;
        r += step_row;
        c += step_col;
    }
    return true;
}

bool chess_piece::can_capture_or_move_to(int to_row, int to_col,
                                         const chessboard& cb) const
{
    const chess_piece* target = cb(to_row, to_col);
    return !target || target->get_color() != get_color();
}
