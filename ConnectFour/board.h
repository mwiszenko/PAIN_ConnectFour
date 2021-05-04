#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsView>
#include "field.h"
#include "constants.h"

class Board : public QGraphicsScene
{
public:
    Board(int columns, int rows, QObject *parent = Q_NULLPTR);
    void setup(int columns, int rows);
    Field* fields[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS];

public slots:

private:

signals:
    void gameWon();
};

#endif // BOARD_H
