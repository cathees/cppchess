#include "MainWindow.h"
#include "ChessboardWidget.h"

#include "../chessboard.h"
#include "../chessboard_factory.h"

#include <QApplication>
#include <QLabel>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QTimer>

MainWindow::MainWindow(chessboard_factory &factory, QWidget *parent)
    : QMainWindow{parent}
    , _factory{factory}
{
    setWindowTitle("SWC3 Chess");

    createMenu();
    loadChessVariant(chess_variant::standard);

    statusBar()->showMessage("Ready");
}

MainWindow::~MainWindow()
{
    delete _chessboard;
}

void MainWindow::createMenu()
{
    QMenu *fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction("&Quit", QKeySequence{"Ctrl+Q"}, qApp, &QApplication::quit);

    QMenu *variantMenu = menuBar()->addMenu("&Variant");
    variantMenu->addAction("&Standard", [this]() { loadChessVariant(chess_variant::standard); });
    variantMenu->addAction("&Random", [this]() { loadChessVariant(chess_variant::random); });
    variantMenu->addAction("&Chess 2.0", [this]() { loadChessVariant(chess_variant::chess_2_0); });

    QMenu *helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction("&About...", [this]() {
        QString text = R"(<p>SWC3 Chess</p>
                          <p>Chess board color scheme and pieces are borrowed from <a href="https://lichess.org">lichess.org</a>, an open-source chess server.</p>
                          <p>Chess pieces by <a href="https://en.wikipedia.org/wiki/User:Cburnett">Colin M.L. Burnett</a> under GPLv2+.</p>)";

        QMessageBox::information(this, "SWC3 Chess", text);
    });
}

void MainWindow::loadChessVariant(chess_variant variant)
{
    takeCentralWidget();
    delete _chessboard;

    _chessboard = _factory.create_chessboard(variant);

    if (_chessboard != nullptr) {
        _chessboardWidget = new ChessboardWidget(*_chessboard);

        connect(_chessboardWidget, &ChessboardWidget::pieceMoved, this, &MainWindow::onPieceMoved);
        connect(_chessboardWidget, &ChessboardWidget::gameOver, this, &MainWindow::onGameOver);

        setCentralWidget(_chessboardWidget);

        statusBar()->showMessage(QString{"New game started. %1 to move."}.arg(
            _chessboard->is_whites_turn() ? "White" : "Black"));
    } else {
        QLabel *notImplementedLabel = new QLabel{this};

        notImplementedLabel->setAlignment(Qt::AlignCenter);
        notImplementedLabel->setStyleSheet("color: gray; font-size: 48px;");
        notImplementedLabel->setText("Not implemented!");

        setCentralWidget(notImplementedLabel);
    }
}

void MainWindow::onPieceMoved(const QPoint &to)
{
    Q_ASSERT(_chessboard != nullptr);
    statusBar()->showMessage(
        QString{"Piece moved to (%1, %2). %3 to move."}.arg(to.x()).arg(to.y()).arg(
            _chessboard->is_whites_turn() ? "White" : "Black"));
}

void MainWindow::onGameOver()
{
    statusBar()->showMessage("Game over!");

    QTimer::singleShot(0, [this]() { QMessageBox::information(this, "SWC3 Chess", "Game over!"); });
}
