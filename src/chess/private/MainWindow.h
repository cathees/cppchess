#pragma once

#include <QMainWindow>

#include "../chessboard_factory.h"

class ChessboardWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(chessboard_factory &factory, QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    void createMenu();

    void loadChessVariant(chess_variant chessVariant);

private slots:
    void onPieceMoved(const QPoint &to);
    void onGameOver();

private:
    chessboard_factory &_factory;
    ChessboardWidget *_chessboardWidget{nullptr};
    chessboard *_chessboard{nullptr};
};
