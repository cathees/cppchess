#pragma once

#include "chess_piece.h"
class chess_piece;
/**
 * @brief Abstract base class representing a chessboard
 */
class chessboard
{
public:
    virtual ~chessboard() = default;

    /**
     * @brief Check if it's white's turn to move
     * @return true if white's turn, false if black's turn
     */
    [[nodiscard]] virtual bool is_whites_turn() const = 0;
    
    /**
     * @brief Check if the game is over
     * @return true if game has ended, false otherwise
     */
    [[nodiscard]] virtual bool is_game_over() = 0;

    /**
     * @brief Get the size of the board (number of rows/columns)
     * @return Board size as integer
     */
    [[nodiscard]] virtual int get_size() const = 0;
    
    /**
     * @brief Access a piece at the given position
     * @param row Row index
     * @param col Column index
     * @return Pointer to chess piece at position, or nullptr if empty
     */
    [[nodiscard]] virtual const chess_piece *operator()(int row, int col) const = 0;

    /**
     * @brief Check if a piece at the given position can be selected by the player whose turn it is.
     * @param row Row index
     * @param col Column index
     * @return true if piece can be selected, false otherwise
     */
    [[nodiscard]] virtual bool can_select_piece(int row, int col) const = 0;

    /**
     * @brief Check if the currently selected piece can move to the given position 
     * possibly capturing an opponent's piece.
     * 
     * @param row Target row index
     * @param col Target column index
     * @return true if move is valid, false otherwise
     */
    [[nodiscard]] virtual bool can_move_selection_to(int row, int col) = 0;

    /**
     * @brief Select a piece at the given position
     * @param row Row index
     * @param col Column index
     */
    virtual void select_piece(int row, int col) = 0;
    
    /**
     * @brief Move the currently selected piece to the given position
     * @param row Target row index
     * @param col Target column index
     */
    virtual void move_selection_to(int row, int col) = 0;    
};
