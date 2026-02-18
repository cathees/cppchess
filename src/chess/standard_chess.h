
#ifndef SWC3CHESS_STANDARD_CHESS_H
#define SWC3CHESS_STANDARD_CHESS_H
#include <array>
#include <memory>
#include <vector>

#include "chessboard.h"


class standard_chess : public chessboard
{
public:
    standard_chess();

    [[nodiscard]] bool is_whites_turn() const;
    [[nodiscard]] bool is_game_over();
    [[nodiscard]] int  get_size() const override;
    [[nodiscard]] const chess_piece* operator()(int row, int col) const override;

    [[nodiscard]] bool can_select_piece(int row, int col) const override;
    [[nodiscard]] bool can_move_selection_to(int row, int col);
    void add_piece(std::unique_ptr<chess_piece> p);
    void select_piece(int row, int col) override;
    void remove_piece(chess_piece* value);
    bool is_checkmate(piece_color color);
    bool is_stalemate(piece_color color);
    void move_selection_to(int row, int col) override;
    bool is_in_check(piece_color color) const;

private:
    std::vector<std::unique_ptr<chess_piece>> m_pieces;
    std::vector<std::vector<chess_piece*>> m_board;
    chess_piece* selected_piece;
    bool white_turn;

};



#endif //SWC3CHESS_STANDARD_CHESS_H