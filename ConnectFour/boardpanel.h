#ifndef BOARDPANEL_H
#define BOARDPANEL_H

#include <QGraphicsView>
#include <QResizeEvent>

class BoardPanel : public QGraphicsView
{
public:
    BoardPanel(QWidget *) { };
    void resizeEvent(QResizeEvent *e);

};

#endif // BOARDPANEL_H
