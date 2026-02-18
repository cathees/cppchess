#include <QApplication>

#include "chessboard_factory.h"
#include "standard_chess.h"
#include "private/MainWindow.h"

class concrete_chessboard_factory : public chessboard_factory
{
    chessboard *create_chessboard(chess_variant variant) override
    {
        switch (variant) {
        case chess_variant::standard:
            return new standard_chess();
            break;
        case chess_variant::random:
            // Return random chessboard implementation
            break;
        case chess_variant::chess_2_0:
            // Return chess 2.0 board implementation
            break;
        }

        return nullptr;
    }
};

int main(int argc, char *argv[])
{
    QApplication app{argc, argv};

    concrete_chessboard_factory factory;
    MainWindow window{factory};

    window.resize(800, 600);
    window.show();

    return app.exec();
}
