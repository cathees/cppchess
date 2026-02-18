#pragma once

#include <QWidget>

class chessboard;

class ChessboardWidget : public QWidget
{
    Q_OBJECT

public:
    ChessboardWidget(chessboard &chessboard, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *) override;

private slots:
    void onSquareClicked(int row, int col);

signals:
    void pieceMoved(QPoint to);
    void gameOver();

private:
    struct Square
    {
        bool selected{false};
        bool highlighted{false};
    };

    void clearSelection();

    [[nodiscard]] Square &squareAt(int row, int col);

    QRect m_boardRect;
    int m_squareSize{0};

    chessboard &m_chessboard;
    QList<Square> m_squares;
};
