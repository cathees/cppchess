#include "chessboard.h"
#include "chessboard_factory.h"

#include "private-cli/chess-cli.h"

#include <iostream>

/**
 * @brief Concrete factory implementation
 */
class concrete_chessboard_factory : public chessboard_factory
{
public:
    chessboard *create_chessboard(chess_variant variant) override
    {
        switch (variant) {
        case chess_variant::standard:
            // TODO: Return standard chessboard implementation
            break;
        case chess_variant::random:
            // TODO: Return random chessboard implementation
            break;
        case chess_variant::chess_2_0:
            // TODO: Return chess 2.0 board implementation
            break;
        }

        return nullptr;
    }
};

int main(int argc, char *argv[])
{
    std::cout << "Swc3Chess CLI\n";

    if (std::string{argv[0]} == "--help") {
        std::cout << "Usage: " << argv[0] << " [variant]\n";
        std::cout << "Variants: standard (default), random, chess2.0\n\n";
    }

    chess_variant variant = parse_command_line(argc, argv);

    concrete_chessboard_factory factory;
    play_game(factory, variant);
    
    return 0;
}
