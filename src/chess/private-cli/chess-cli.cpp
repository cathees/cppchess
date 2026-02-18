#include "chess-cli.h"
#include "../chessboard.h"
#include "../chessboard_factory.h"

#include <iostream>
#include <sstream>
#include <cctype>
#include <string>

/**
 * @brief Displays the chessboard with possible moves
 * @param board The chessboard
 * @param selected_row Row of the selected piece (-1 if none selected)
 * @param selected_col Column of the selected piece (-1 if none selected)
 */
static void display_board(const chessboard &board, int selected_row = -1, int selected_col = -1)
{
    // Header with column numbers
    std::cout << "   ";
    for (int col = 0; col < board.get_size(); ++col) {
        std::cout << " " << col << " ";
    }
    std::cout << "\n";

    for (int row = 0; row < board.get_size(); ++row) {
        // Row number
        std::cout << " " << row << " ";

        for (int col = 0; col < board.get_size(); ++col) {
            const chess_piece *piece = board(row, col);

            // Check if field should be marked
            bool is_selected = (row == selected_row && col == selected_col);
            bool is_possible_move = (selected_row != -1 && board.can_move_selection_to(row, col));

            if (is_selected) {
                // Selected piece in parentheses
                std::cout << "(";
                if (piece != nullptr) {
                    char symbol = piece->get_symbol();
                    if (piece->get_color() == piece_color::white) {
                        std::cout << static_cast<char>(std::toupper(symbol));
                    } else {
                        std::cout << static_cast<char>(std::tolower(symbol));
                    }
                } else {
                    std::cout << ".";
                }
                std::cout << ")";
            } else if (is_possible_move) {
                // Possible move in square brackets
                std::cout << "[";
                if (piece != nullptr) {
                    char symbol = piece->get_symbol();
                    if (piece->get_color() == piece_color::white) {
                        std::cout << static_cast<char>(std::toupper(symbol));
                    } else {
                        std::cout << static_cast<char>(std::tolower(symbol));
                    }
                } else {
                    std::cout << ".";
                }
                std::cout << "]";
            } else {
                // Normal display
                std::cout << " ";
                if (piece != nullptr) {
                    char symbol = piece->get_symbol();
                    if (piece->get_color() == piece_color::white) {
                        std::cout << static_cast<char>(std::toupper(symbol));
                    } else {
                        std::cout << static_cast<char>(std::tolower(symbol));
                    }
                } else {
                    std::cout << ".";
                }
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

/**
 * @brief Reads a valid coordinate pair from the user in format "row, col"
 * @param prompt Display text
 * @param max_value Maximum value (exclusive)
 * @param row Output parameter for row
 * @param col Output parameter for column
 * @return true if input was valid, false otherwise
 */
static bool get_coordinates(const std::string &prompt, int max_value, int &row, int &col)
{
    std::string line;
    std::cout << prompt << " ";

    if (!std::getline(std::cin, line)) {
        return false;
    }

    // Simple parsing: replace comma with space and use stringstream
    for (char &c : line) {
        if (c == ',') {
            c = ' ';
        }
    }

    std::istringstream iss(line);
    if (iss >> row >> col) {
        // Check if there are extra characters after the two numbers
        std::string extra;
        if (!(iss >> extra)) {
            // No extra input, validate range
            if (row >= 0 && row < max_value && col >= 0 && col < max_value) {
                return true;
            }
        }
    }

    std::cout << "Invalid input! Please enter coordinates in format 'row, col' "
              << "(e.g., '0, 1') with values between 0 and " << (max_value - 1) << ".\n";
    return false;
}

/**
 * @brief Parse command line arguments to determine chess variant
 * @param argc Argument count
 * @param argv Argument values
 * @return Chess variant to play
 */
chess_variant parse_command_line(int argc, char *argv[])
{
    if (argc > 1) {
        std::string variant_str{argv[1]};

        if (variant_str == "standard") {
            return chess_variant::standard;
        } else if (variant_str == "random") {
            return chess_variant::random;
        } else if (variant_str == "chess2.0") {
            return chess_variant::chess_2_0;
        } else {
            std::cout << "Unknown variant '" << argv[1] << "'. Using standard.\n";
        }
    }
    
    // Default to standard
    return chess_variant::standard;
}

/**
 * @brief Main game loop
 */
void play_game(chessboard_factory &factory, chess_variant variant)
{
    chessboard *board = factory.create_chessboard(variant);

    if (board == nullptr) {
        std::cout << "Not implemented!.\n";
        return;
    }

    std::cout << "\n=== Swc3Chess ===\n";
    std::cout << "Uppercase = White, Lowercase = Black\n";
    std::cout << "(X) = selected piece, [X] = possible move\n";

    while (!board->is_game_over()) {
        display_board(*board);

        std::cout << (board->is_whites_turn() ? "White" : "Black") << " to move." << std::endl;

        int from_row = -1;
        int from_col = -1;
        while (true) {
            if (get_coordinates("Select piece (row, col): ", board->get_size(), from_row, from_col)) {
                if (board->can_select_piece(from_row, from_col)) {
                    board->select_piece(from_row, from_col);
                    break;
                }
                std::cout << "No valid piece at this position! Try again.\n\n";
            }
        }

        std::cout << "\nPossible moves:\n";
        display_board(*board, from_row, from_col);

        int to_row = -1;
        int to_col = -1;
        while (true) {
            if (get_coordinates("Select target (row, col): ", board->get_size(), to_row, to_col)) {
                if (board->can_move_selection_to(to_row, to_col)) {
                    board->move_selection_to(to_row, to_col);
                    break;
                }
                std::cout << "Invalid move! Try again.\n";
            }
        }

        std::cout << "\n";
    }

    std::cout << "\n=== Game Over! ===\n";
    display_board(*board);
    std::cout << (board->is_whites_turn() ? "Black" : "White") << " wins!\n";
    
    delete board;
}
