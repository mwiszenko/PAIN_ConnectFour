#include "field.h"
#include "constants.h"
#include <QtGui>

Field::Field(qreal width, qreal height, int column, int row) : player(0)
{
    this->setRect(0, 0, width, height);
    this->isPressed = false;
    if(row == NUMBER_OF_ROWS - 1) {
        this->isAvailable = true;
    } else {
        this->isAvailable = false;
    }
    this->isInteractive = true;
    this->column = column;
    this->row = row;
}

void Field::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen borderPen;
    borderPen.setWidth(0);
    if(isInteractive && isAvailable) {
        painter->setBrush(QBrush(Qt::green));
    } else if(!isInteractive && isAvailable) {
        painter->setBrush(QBrush(Qt::darkGreen));
    } else if(isInteractive && !isAvailable && isPressed) {
        painter->setBrush(QBrush(Qt::darkRed));
    } else {
        painter->setBrush(QBrush(Qt::lightGray));
    }

    painter->setPen(borderPen);
    painter->drawRect(this->rect());
}

void Field::setInteractive(bool available) {
    this->isInteractive = available;
    update();
}

void Field::setAvailable(bool available) {
    this->isAvailable = available;
    update();
}

bool Field::getAvailable() {
    return this->isAvailable;
}

void Field::setPlayer(int player) {
    this->player = player;
}

int Field::getPlayer() {
    return this->player;
}


void Field::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if(isInteractive) {
        isPressed = true;
        update();
    }
}

void Field::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    if(isInteractive) {
        isPressed = false;
        update();
        if(isAvailable) {
            emit fieldClicked(column, row);
        }
    }
}
