#pragma once

class chessboard;
class chessboard_factory;
enum class chess_variant;

/**
 * @brief Parse command line arguments to determine chess variant
 * @param argc Argument count
 * @param argv Argument values
 * @return Chess variant to play
 */
chess_variant parse_command_line(int argc, char *argv[]);

/**
 * @brief Main game loop
 * @param factory Factory to create chessboard
 * @param variant Chess variant to play
 */
void play_game(chessboard_factory &factory, chess_variant variant);
