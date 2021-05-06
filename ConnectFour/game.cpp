#include "game.h"
#include "field.h"
#include "board.h"
#include "constants.h"

#include <QGraphicsItemAnimation>
#include <QTimeLine>

Game::Game() : animationSpeed(MEDIUM_ANIMATION_SPEED), currentPlayer(1)
{
    board = new Board(NUMBER_OF_COLUMNS, NUMBER_OF_ROWS);
    for(int i = 0; i < NUMBER_OF_ROWS; ++i) {
        for(int j = 0; j < NUMBER_OF_COLUMNS; ++j) {
            connect(board->fields[i][j], &Field::fieldClicked, this, &Game::processClick);
        }
    }
}

void Game::newGame() {
    currentPlayer = 1;
    board = new Board(NUMBER_OF_COLUMNS, NUMBER_OF_ROWS);
    for(int i = 0; i < NUMBER_OF_ROWS; ++i) {
        for(int j = 0; j < NUMBER_OF_COLUMNS; ++j) {
            connect(board->fields[i][j], &Field::fieldClicked, this, &Game::processClick);
        }
    }
}

void Game::processClick(int col, int row) {
    board->fields[row][col]->setPlayer(currentPlayer);

    QBrush brush;
    QPen borderPen;
    if(currentPlayer == 1) {
        brush = QBrush(Qt::red);
        borderPen = QPen(Qt::red);
    } else {
        brush = QBrush(Qt::blue);
        borderPen = QPen(Qt::blue);
    }
    borderPen.setWidth(0);

    QGraphicsPixmapItem * block;
    if(currentPlayer == 1) {
        block = new QGraphicsPixmapItem(QPixmap(":/img/red_block.png").scaled(BLOCK_WIDTH, BLOCK_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        block = new QGraphicsPixmapItem(QPixmap(":/img/blue_block.png").scaled(BLOCK_WIDTH, BLOCK_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    if(animationSpeed != INSTANT_ANIMATION_SPEED) {
        block->setPos((FIELD_WIDTH + FIELD_WIDTH_OFFSET) * col + (FIELD_WIDTH - BLOCK_WIDTH) / 2, (FIELD_WIDTH - BLOCK_WIDTH) / 2);

        QTimeLine *timer = new QTimeLine(animationSpeed * (row + 1));
        timer->setFrameRange(0, 100);

        QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
        animation->setItem(block);
        animation->setTimeLine(timer);

        animation->setPosAt(1, QPointF((FIELD_WIDTH + FIELD_WIDTH_OFFSET) * col + (FIELD_WIDTH - BLOCK_WIDTH) / 2, (FIELD_HEIGHT + FIELD_HEIGHT_OFFSET) * row + (FIELD_WIDTH - BLOCK_WIDTH) / 2));

        board->addItem(block);

        connect(timer, SIGNAL(finished()), this, SLOT(setFieldsInteractive()));

        timer->start();

        setFieldsNoninteractive();
        emit nextTurn(0);
        setFieldAvailability(col, row);

    } else {
        block->setPos((FIELD_WIDTH + FIELD_WIDTH_OFFSET) * col + (FIELD_WIDTH - BLOCK_WIDTH) / 2, (FIELD_HEIGHT + FIELD_HEIGHT_OFFSET) * row + (FIELD_WIDTH - BLOCK_WIDTH) / 2);

        board->addItem(block);

        setFieldsNoninteractive();
        emit nextTurn(0);
        setFieldAvailability(col, row);
        setFieldsInteractive();
    }
}

void Game::setFieldAvailability(int col, int row) {
        board->fields[row][col]->setAvailable(false);
        if(row >= 1) {
            board->fields[row-1][col]->setAvailable(true);
        }
}

void Game::setFieldsNoninteractive() {
    for(int i = 0; i < NUMBER_OF_ROWS; ++i) {
        for(int j = 0; j < NUMBER_OF_COLUMNS; ++j) {
            board->fields[i][j]->setInteractive(false);
        }
    }
}

void Game::setFieldsInteractive() {
    for(int i = 0; i < NUMBER_OF_ROWS; ++i) {
        for(int j = 0; j < NUMBER_OF_COLUMNS; ++j) {
            board->fields[i][j]->setInteractive(true);
        }
    }
    if(currentPlayer == 1) {
        currentPlayer = 2;
        if(!hasGameFinished(1)) {
            emit nextTurn(2);
        }
    } else {
        currentPlayer = 1;
        if(!hasGameFinished(2)) {
            emit nextTurn(1);
        }
    }
}

bool Game::hasGameFinished(int player){
    if(verticalCheck(player) || horizontalCheck(player) || ascendingDiagonalCheck(player) || descendingDiagonalCheck(player)) {
        for (int i = 0; i < NUMBER_OF_ROWS; ++i) {
            for (int j = 0; j < NUMBER_OF_COLUMNS; ++j) {
                board->fields[i][j]->setAvailable(false);
            }
        }
        emit gameEnded(player);
        return true;
    } else if(hasGameBeenDrawn()) {
        emit gameEnded(0);
        return true;
    }
    return false;
}

bool Game::verticalCheck(int player) {
    for (int i = 0; i < NUMBER_OF_ROWS - 3; ++i) {
        for (int j = 0; j < NUMBER_OF_COLUMNS; ++j) {
            if (board->fields[i][j]->getPlayer() == player && board->fields[i+1][j]->getPlayer() == player
                    && board->fields[i+2][j]->getPlayer() == player && board->fields[i+3][j]->getPlayer() == player) {
                drawWinningLine(i, j, i+3, j);
                return true;
            }
        }
    }
    return false;
}

bool Game::horizontalCheck(int player) {
    for (int i = 0; i < NUMBER_OF_ROWS; ++i) {
        for (int j = 0; j < NUMBER_OF_COLUMNS - 3; ++j) {
            if (board->fields[i][j]->getPlayer() == player && board->fields[i][j+1]->getPlayer() == player
                    && board->fields[i][j+2]->getPlayer() == player && board->fields[i][j+3]->getPlayer() == player) {
                drawWinningLine(i, j, i, j+3);
                return true;
            }
        }
    }
    return false;
}

bool Game::ascendingDiagonalCheck(int player) {
    for (int i = 3; i < NUMBER_OF_ROWS; ++i) {
        for (int j = 0; j < NUMBER_OF_COLUMNS - 3; ++j) {
            if (board->fields[i][j]->getPlayer() == player && board->fields[i-1][j+1]->getPlayer() == player
                    && board->fields[i-2][j+2]->getPlayer() == player && board->fields[i-3][j+3]->getPlayer() == player) {
                drawWinningLine(i, j, i-3, j+3);
                return true;
            }
        }
    }
    return false;
}

bool Game::descendingDiagonalCheck(int player) {
    for (int i = 3; i < NUMBER_OF_ROWS; ++i) {
        for (int j = 3; j < NUMBER_OF_COLUMNS; ++j) {
            if (board->fields[i][j]->getPlayer() == player && board->fields[i-1][j-1]->getPlayer() == player
                    && board->fields[i-2][j-2]->getPlayer() == player && board->fields[i-3][j-3]->getPlayer() == player) {
                drawWinningLine(i, j, i-3, j-3);
                return true;
            }
        }
    }
    return false;
}

void Game::drawWinningLine(int y1, int x1, int y2, int x2) {
    QGraphicsLineItem *line = new QGraphicsLineItem((FIELD_WIDTH + FIELD_WIDTH_OFFSET) * x1 + FIELD_WIDTH / 2, (FIELD_HEIGHT + FIELD_HEIGHT_OFFSET) * y1 + FIELD_HEIGHT / 2,
                                                    (FIELD_WIDTH + FIELD_WIDTH_OFFSET) * x2 + FIELD_WIDTH / 2, (FIELD_HEIGHT + FIELD_HEIGHT_OFFSET) * y2 + FIELD_HEIGHT / 2);
    QPen pen;
    pen.setWidth(10);
    pen.setColor(Qt::darkYellow);
    line->setPen(pen);
    board->addItem(line);
}

bool Game::hasGameBeenDrawn(){
    for (int i = 0; i < NUMBER_OF_ROWS; ++i) {
        for (int j = 0; j < NUMBER_OF_COLUMNS; ++j) {
            if(board->fields[i][j]->getAvailable()) {
                return false;
            }
        }
    }
    return true;
}

void Game::settingsChanged(QStringList settings) {
    switch(settings[0].toInt()) {
    case 0:
        animationSpeed = VERY_SLOW_ANIMATION_SPEED;
        break;
    case 1:
        animationSpeed = SLOW_ANIMATION_SPEED;
        break;
    case 2:
        animationSpeed = MEDIUM_ANIMATION_SPEED;
        break;
    case 3:
        animationSpeed = FAST_ANIMATION_SPEED;
        break;
    case 4:
        animationSpeed = VERY_FAST_ANIMATION_SPEED;
        break;
    case 5:
        animationSpeed = INSTANT_ANIMATION_SPEED;
        break;
    default:
        animationSpeed = MEDIUM_ANIMATION_SPEED;
        break;
    }
}
