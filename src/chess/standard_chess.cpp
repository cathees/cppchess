#include "standard_chess.h"

#include <algorithm>
#include <qassert.h>

#include "pieces/bishop.h"
#include "pieces/king.h"
#include "pieces/knight.h"
#include "pieces/pawn.h"
#include "pieces/queen.h"
#include "pieces/rook.h"

standard_chess::standard_chess() : m_board(8, std::vector<chess_piece*>(8, nullptr))
{
    white_turn = true;
    selected_piece = nullptr;
    // instantiate pieces
    auto w_king_ptr = std::make_unique<king>('K', piece_color::white, 7, 4);
    auto b_king_ptr = std::make_unique<king>('K', piece_color::black, 0, 4);

    auto w_queen_ptr = std::make_unique<queen>('Q', piece_color::white, 7, 3);
    auto b_queen_ptr = std::make_unique<queen>('Q', piece_color::black, 0, 3);

    auto w_bishop1_ptr = std::make_unique<bishop>('B', piece_color::white, 7, 2);
    auto w_bishop2_ptr = std::make_unique<bishop>('B', piece_color::white, 7, 5);
    auto b_bishop1_ptr = std::make_unique<bishop>('B', piece_color::black, 0, 2);
    auto b_bishop2_ptr = std::make_unique<bishop>('B', piece_color::black, 0, 5);

    auto w_knight1_ptr = std::make_unique<knight>('N', piece_color::white, 7, 1);
    auto w_knight2_ptr = std::make_unique<knight>('N', piece_color::white, 7, 6);
    auto b_knight1_ptr = std::make_unique<knight>('N', piece_color::black, 0, 1);
    auto b_knight2_ptr = std::make_unique<knight>('N', piece_color::black, 0, 6);

    auto w_rook1_ptr = std::make_unique<rook>('R', piece_color::white, 7, 0);
    auto w_rook2_ptr = std::make_unique<rook>('R', piece_color::white, 7, 7);
    auto b_rook1_ptr = std::make_unique<rook>('R', piece_color::black, 0, 0);
    auto b_rook2_ptr = std::make_unique<rook>('R', piece_color::black, 0, 7);

    for (int col = 0; col < 8; col++)
    {
        auto w_pawn_ptr = std::make_unique<pawn>('P', piece_color::white, 6, col);
        auto b_pawn_ptr = std::make_unique<pawn>('P', piece_color::black, 1, col);
        add_piece(std::move(w_pawn_ptr));
        add_piece(std::move(b_pawn_ptr));
    }
    
    add_piece(std::move(w_king_ptr));
    add_piece(std::move(b_king_ptr));
    add_piece(std::move(w_queen_ptr));
    add_piece(std::move(b_queen_ptr));
    add_piece(std::move(w_bishop1_ptr));
    add_piece(std::move(w_bishop2_ptr));
    add_piece(std::move(b_bishop1_ptr));
    add_piece(std::move(b_bishop2_ptr));
    add_piece(std::move(w_knight1_ptr));
    add_piece(std::move(w_knight2_ptr));
    add_piece(std::move(b_knight1_ptr));
    add_piece(std::move(b_knight2_ptr));
    add_piece(std::move(w_rook1_ptr));
    add_piece(std::move(w_rook2_ptr));
    add_piece(std::move(b_rook1_ptr));
    add_piece(std::move(b_rook2_ptr));
};

bool standard_chess::is_whites_turn() const
{
    return white_turn;
}

bool standard_chess::is_game_over()
{

    return is_checkmate(piece_color::white) ||
           is_checkmate(piece_color::black) ||
           is_stalemate(piece_color::white) ||
           is_stalemate(piece_color::black);
}


int standard_chess::get_size() const {
    return 8;
}

const chess_piece* standard_chess::operator()(int row, int col) const {
    return m_board[abs(row)][abs(col)];
}

bool standard_chess::can_select_piece(int row, int col) const
{
    chess_piece* p = m_board[row][col];
    if (p == nullptr) return false;
    if (is_whites_turn() && p->get_color() == piece_color::white)
    {
        return true;
    }
    if (!is_whites_turn() && p->get_color() == piece_color::black)
    {
        return true;
    }
    return false;
}

bool standard_chess::can_move_selection_to(int row, int col)
{
    if (!selected_piece)
        return false;

    // cannot move onto own piece
    chess_piece* target = m_board[row][col];
    if (target && target->get_color() == selected_piece->get_color())
        return false;

    // piece-level legality
    if (!selected_piece->can_move(row, col, *this))
        return false;

    int from_r = selected_piece->get_row();
    int from_c = selected_piece->get_col();

    // --- castling handling ---
    if (auto* k = dynamic_cast<king*>(selected_piece)) {
        int dc = col - from_c;

        if (std::abs(dc) == 2) {
            if (is_in_check(k->get_color()))
                return false;

            int step = (dc > 0) ? 1 : -1;

            m_board[from_r][from_c] = nullptr;
            m_board[from_r][from_c + step] = k;
            k->set_col(from_c + step);

            bool intermediate_check = is_in_check(k->get_color());

            // undo
            m_board[from_r][from_c + step] = nullptr;
            m_board[from_r][from_c] = k;
            k->set_col(from_c);

            if (intermediate_check)
                return false;
        }
    }

    // --- simulate final move ---
    chess_piece* captured = m_board[row][col];

    m_board[from_r][from_c] = nullptr;
    m_board[row][col] = selected_piece;
    selected_piece->set_row(row);
    selected_piece->set_col(col);

    bool still_in_check = is_in_check(selected_piece->get_color());

    // --- undo ---
    m_board[from_r][from_c] = selected_piece;
    m_board[row][col] = captured;
    selected_piece->set_row(from_r);
    selected_piece->set_col(from_c);

    return !still_in_check;
}



void standard_chess::select_piece(int row, int col) {
    selected_piece = m_board[row][col];
}

void standard_chess::move_selection_to(int row, int col)
{
    if (!selected_piece)
        return;

    int from_row = selected_piece->get_row();
    int from_col = selected_piece->get_col();

    // --- castling handling ---
    if (auto* k = dynamic_cast<king*>(selected_piece)) {
        int dc = col - from_col;

        if (std::abs(dc) == 2) {
            int rook_from_col = (dc > 0) ? get_size() - 1 : 0;
            int rook_to_col   = from_col + (dc > 0 ? 1 : -1);

            chess_piece* rook_piece = m_board[from_row][rook_from_col];

            m_board[from_row][rook_from_col] = nullptr;
            m_board[from_row][rook_to_col] = rook_piece;

            rook_piece->set_row(from_row);
            rook_piece->set_col(rook_to_col);

            static_cast<rook*>(rook_piece)->has_moved = true;
        }

        k->has_moved = true;
    }

    // --- capture handling ---
    if (m_board[row][col]) {
        remove_piece(m_board[row][col]);
    }

    // --- move piece ---
    m_board[from_row][from_col] = nullptr;
    m_board[row][col] = selected_piece;

    selected_piece->set_row(row);
    selected_piece->set_col(col);

    // --- pawn promotion ---
    if (auto* p = dynamic_cast<pawn*>(selected_piece)) {
        bool promote =
            (p->get_color() == piece_color::white && row == 0) ||
            (p->get_color() == piece_color::black && row == get_size() - 1);

        if (promote) {
            piece_color color = p->get_color();

            remove_piece(p);

            auto q = std::make_unique<queen>('Q', color, row, col);
            chess_piece* qptr = q.get();
            m_pieces.push_back(std::move(q));

            m_board[row][col] = qptr;

            selected_piece = nullptr;
            white_turn = !white_turn;
            return;
        }
    }

    if (auto* r = dynamic_cast<rook*>(selected_piece))
        r->has_moved = true;

    selected_piece = nullptr;
    white_turn = !white_turn;
}





void standard_chess::add_piece(std::unique_ptr<chess_piece> p) {
    m_board[p->get_row()][p->get_col()] = p.get();
    m_pieces.push_back(std::move(p));
}

bool standard_chess::is_in_check(piece_color color) const
{
    const chess_piece* king = nullptr;

    for (const auto& p : m_pieces) {
        if (p->get_color() == color && p->is_essential()) {
            king = p.get();
            break;
        }
    }

    if (!king)
        return false;

    int king_row = king->get_row();
    int king_col = king->get_col();

    for (const auto& p : m_pieces)
    {
        if (p->get_color() == color)
            continue;

        int r = p->get_row();
        int c = p->get_col();

        if (r < 0 || c < 0)
            continue;

        if (m_board[r][c] != p.get())
            continue;

        if (p->controls(king_row, king_col, *this))
            return true;
    }

    return false;
}


void standard_chess::remove_piece(chess_piece* piece)
{
    if (!piece)
        return;

    // remove from owning container
    auto it = std::remove_if(
        m_pieces.begin(),
        m_pieces.end(),
        [piece](const std::unique_ptr<chess_piece>& p) {
            return p.get() == piece;
        }
    );

    m_pieces.erase(it, m_pieces.end());
}

bool standard_chess::is_checkmate(piece_color color)
{
    if (!is_in_check(color))
        return false;

    chess_piece* saved = selected_piece;

    for (const auto& p : m_pieces) {
        if (p->get_color() != color)
            continue;

        selected_piece = p.get();

        for (int r = 0; r < get_size(); ++r) {
            for (int c = 0; c < get_size(); ++c) {
                if (can_move_selection_to(r, c)) {
                    selected_piece = saved;
                    return false; // es gibt eine Verteidigung
                }
            }
        }
    }

    selected_piece = saved;
    return true; // kein legaler Zug → Matt
}



bool standard_chess::is_stalemate(piece_color color)
{
    if (is_in_check(color))
        return false;

    chess_piece* saved = selected_piece;

    for (const auto& p : m_pieces) {
        if (p->get_color() != color)
            continue;

        selected_piece = p.get();

        for (int r = 0; r < get_size(); ++r) {
            for (int c = 0; c < get_size(); ++c) {
                if (can_move_selection_to(r, c)) {
                    selected_piece = saved;
                    return false;
                }
            }
        }
    }

    selected_piece = saved;
    return true;
}



