#include "board.h"
#include "field.h"
#include "constants.h"

#include <QGraphicsItemAnimation>
#include <QTimeLine>

Board::Board(int columns, int rows, QObject* parent)
{
    setup(columns, rows);
}

void Board::setup(int columns, int rows)
{
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            Field* f = new Field(FIELD_WIDTH, FIELD_HEIGHT, j, i);
            f->setPos((FIELD_WIDTH + FIELD_WIDTH_OFFSET) * j, (FIELD_HEIGHT + FIELD_HEIGHT_OFFSET) * i);
            this->addItem(f);
            fields[i][j] = f;
        }
    }
}
