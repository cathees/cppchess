#include "ChessboardWidget.h"

#include <QFile>
#include <QMouseEvent>
#include <QPainter>
#include <QSvgRenderer>

#include "../chessboard.h"
#include "../chess_piece.h"
namespace {
// Color palette taken from https://lichess.org, board "brown"
constexpr QColor darkSquareColor{181, 136, 99};
constexpr QColor selectedDarkSquareColor{100, 111, 64};
constexpr QColor lightSquareColor{240, 217, 181};
constexpr QColor selectedLightSquareColor{174, 177, 135};
constexpr QColor highlightColor{100, 111, 64};
} // namespace

ChessboardWidget::ChessboardWidget(chessboard &chessboard, QWidget *parent)
    : QWidget{parent}
    , m_chessboard{chessboard}
    , m_squares{chessboard.get_size() * chessboard.get_size()}
{}

void ChessboardWidget::paintEvent(QPaintEvent *)
{
    QPainter painter{this};

    painter.setRenderHint(QPainter::Antialiasing);

    for (int col = 0; col < m_chessboard.get_size(); col++) {
        for (int row = 0; row < m_chessboard.get_size(); row++) {
            bool isLightSquare = (col + row) % 2 == 0;

            QColor squareColor = isLightSquare ? lightSquareColor : darkSquareColor;
            QColor selectedSquareColor = isLightSquare ? selectedLightSquareColor
                                                       : selectedDarkSquareColor;

            QRect squareRect{m_boardRect.left() + col * m_squareSize,
                             m_boardRect.top() + row * m_squareSize,
                             m_squareSize,
                             m_squareSize};

            painter.fillRect(squareRect,
                             squareAt(row, col).selected ? selectedSquareColor : squareColor);

            // Draw coordinates on rim squares.
            if (col == 0 || row == 0) {
                int xPos = squareRect.left() + 4;
                int yPos = squareRect.top() + painter.fontMetrics().height() + 2;
                painter.setPen(isLightSquare ? darkSquareColor : lightSquareColor);
                painter.drawText(xPos, yPos, QString::number(col == 0 ? row : col));
            }

            // Draw chess pieces.
            if (const chess_piece *piece = m_chessboard(row, col); piece != nullptr) {
                QChar colorPrefix = piece->get_color() == piece_color::white ? 'w' : 'b';
                QChar pieceSymbol = piece->get_symbol();
                QString fileName
                    = QString{":/src/chess/resources/%1%2"}.arg(colorPrefix).arg(pieceSymbol);

                if (QString svgFileName = fileName + ".svg"; QFile::exists(svgFileName)) {
                    QSvgRenderer svgRenderer{svgFileName};
                    svgRenderer.render(&painter, squareRect);
                } else if (QString pngFileName = fileName + ".png"; QFile::exists(pngFileName)) {
                    QImage image{pngFileName};
                    painter.drawImage(squareRect, image);
                } else {
                    painter.save();
                    // Fall back to drawing a letter.
                    painter.setPen(piece->get_color() == piece_color::white ? Qt::white : Qt::black);
                    auto font = painter.font();
                    font.setPixelSize(static_cast<int>(m_squareSize * 0.8));
                    painter.setFont(font);
                    painter.drawText(squareRect, Qt::AlignCenter, pieceSymbol);
                    painter.restore();
                }
            }

            // Draw markings for available moves.
            if (squareAt(row, col).highlighted) {
                int radius = static_cast<int>(m_squareSize * 0.1);
                painter.setBrush(QBrush{highlightColor});
                painter.setPen(Qt::NoPen);
                painter.drawEllipse(squareRect.center(), radius, radius);
            }
        }
    }
}

void ChessboardWidget::mousePressEvent(QMouseEvent *event)
{
    if (!m_chessboard.is_game_over() && event->button() == Qt::LeftButton
        && m_boardRect.contains(event->pos())) {
        QPoint boardPos = event->pos() - m_boardRect.topLeft();

        int row = boardPos.y() / m_squareSize;
        int col = boardPos.x() / m_squareSize;

        onSquareClicked(row, col);
    }
}

void ChessboardWidget::resizeEvent(QResizeEvent *)
{
    int boardSize = std::min(width(), height());
    int boardXPos = (width() - boardSize) / 2;
    int boardYPos = (height() - boardSize) / 2;

    m_boardRect = QRect{boardXPos, boardYPos, boardSize, boardSize};
    m_squareSize = boardSize / m_chessboard.get_size();
}

void ChessboardWidget::onSquareClicked(int row, int col)
{
    if (m_chessboard.can_select_piece(row, col)) {
        clearSelection();

        m_chessboard.select_piece(row, col);
        squareAt(row, col).selected = true;

        for (int toRow = 0; toRow < m_chessboard.get_size(); toRow++) {
            for (int toCol = 0; toCol < m_chessboard.get_size(); toCol++) {
                bool highlighted = m_chessboard.can_move_selection_to(toRow, toCol);
                squareAt(toRow, toCol).highlighted = highlighted;
            }
        }
    } else if (m_chessboard.can_move_selection_to(row, col)) {
        m_chessboard.move_selection_to(row, col);
        clearSelection();

        if (m_chessboard.is_game_over()) {
            emit gameOver();
        } else {
            emit pieceMoved({row, col});
        }
    }

    update();
}

void ChessboardWidget::clearSelection()
{
    for (auto &square : m_squares) {
        square.selected = false;
        square.highlighted = false;
    }
}

ChessboardWidget::Square &ChessboardWidget::squareAt(int row, int col)
{
    Q_ASSERT(row >= 0 && row < m_chessboard.get_size());
    Q_ASSERT(col >= 0 && col < m_chessboard.get_size());
    return m_squares[m_chessboard.get_size() * row + col];
}
