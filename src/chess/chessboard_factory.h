#pragma once 

#include "chessboard.h"

enum class chess_variant { standard, random, chess_2_0 };

class chessboard_factory {
public:
    [[nodiscard]] virtual chessboard* create_chessboard(chess_variant variant) = 0;
};