#ifndef FIELD_H
#define FIELD_H

#include <QGraphicsRectItem>

class Field: public QObject, public QGraphicsRectItem
{
    Q_OBJECT

    private:
        int player;
        int column;
        int row;
        qreal width;
        qreal height;
        bool isInteractive;
        bool isAvailable;
        bool isPressed;

    public:
        Field(qreal width, qreal height, int column, int row);
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        void setInteractive(bool available);
        void setAvailable(bool available);
        bool getAvailable();
        int getPlayer();
        void setPlayer(int player);

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *e);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);

    signals:
        void fieldClicked(int column, int row);
};

#endif // FIELD_H
