

#ifndef SWC3CHESS_KING_H
#define SWC3CHESS_KING_H
#include <cstdio>

#include "../chess_piece.h"


class king : public chess_piece
{
public:

    king(char symbol, piece_color color, int initial_row, int initial_col)
    : chess_piece(symbol, color, initial_row, initial_col) {}

    [[nodiscard]] bool is_essential() const override;
    [[nodiscard]] bool can_move(int to_row, int to_col, const chessboard& cb) const override;
    [[nodiscard]] bool controls(int row, int col, const chessboard& cb) const override;

    bool has_moved = false;

};


#endif //SWC3CHESS_KING_H