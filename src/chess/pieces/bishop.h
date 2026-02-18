//
// Created by kamui on 12/21/2025.
//

#ifndef SWC3CHESS_BISHOP_H
#define SWC3CHESS_BISHOP_H
#include "../chess_piece.h"


class bishop : public chess_piece
{
public:

    bishop(char symbol, piece_color color, int initial_row, int initial_col)
    : chess_piece(symbol, color, initial_row, initial_col) {}

    [[nodiscard]] bool is_essential() const override;
    [[nodiscard]] bool can_move(int to_row, int to_col, const chessboard& cb) const override;
    [[nodiscard]] bool controls(int row, int col, const chessboard& cb) const override;
};


#endif //SWC3CHESS_BISHOP_H