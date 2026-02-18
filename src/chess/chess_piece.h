#pragma once
#include "chessboard.h"
class chessboard;

/** @brief Color of a chess piece */
enum class piece_color { black, white };

/**
 * @brief Abstract base class representing a chess piece
 */
class chess_piece
{
public:
    virtual ~chess_piece() = default;

    /**
     * @brief Get the symbol representing this piece. 
     * 
     * Built-in symbols are 'B', 'K', 'P', 'Q', and 'R'.
     * 
     * @return Character symbol of the piece
     */
    [[nodiscard]] char get_symbol() const { return m_symbol; }
    
    /**
     * @brief Get the color of this piece
     * @return Color of the piece (black or white)
     */
    [[nodiscard]] piece_color get_color() const { return m_color; }
    
    /**
     * @brief Get the current row position of this piece
     * @return Row index
     */
    [[nodiscard]] int get_row() const { return m_row; }
    
    /**
     * @brief Get the current column position of this piece
     * @return Column index
     */
    [[nodiscard]] int get_col() const { return m_col; }

    /**
     * @brief Set the row position of this piece
     * @param row New row index
     */
    void set_row(int row) { m_row = row; }
    
    /**
     * @brief Set the column position of this piece
     * @param col New column index
     */
    void set_col(int col) { m_col = col; }


    /**
     * @brief Check if this piece is essential (e.g., king)
     * @return true if piece is essential, false otherwise
     */
    [[nodiscard]] virtual bool is_essential() const = 0;



    /**
     * @brief Check if this piece can move to the given square, possibly capturing an opponent's piece.
     * @param to_row Target row index
     * @param to_col Target column index
     * @param cb Reference to the chessboard
     * @return true if move is valid, false otherwise
     */
    [[nodiscard]] virtual bool can_move(int to_row, int to_col, const chessboard &cb) const = 0;

    /**
     * @brief Check if this piece controls the given square
     * 
     * A square is controlled if this piece can move to it, attacks an opponent's piece on it, 
     * or defends its own piece on that square.
     * 
     * @param row Row index to check
     * @param col Column index to check
     * @param cb Reference to the chessboard
     * @return true if position is controlled, false otherwise
     */
    [[nodiscard]] virtual bool controls(int row, int col, const chessboard &cb) const = 0;

protected:
    /**
     * @brief Construct a chess piece
     * @param symbol Character symbol representing the piece
     * @param color Color of the piece
     * @param initial_row Initial row position
     * @param initial_col Initial column position
     */
    chess_piece(char symbol, piece_color color, int initial_row, int initial_col)
        : m_symbol{symbol}
        , m_color{color}
        , m_row{initial_row}
        , m_col{initial_col}
    {}

    bool is_clear_path(int to_row, int to_col,
                       int step_row, int step_col,
                       const chessboard& cb) const;

    bool can_capture_or_move_to(int to_row, int to_col,
                                const chessboard& cb) const;



private:
    char m_symbol{'\0'};
    piece_color m_color{piece_color::white};
    int m_row{-1};
    int m_col{-1};
};
