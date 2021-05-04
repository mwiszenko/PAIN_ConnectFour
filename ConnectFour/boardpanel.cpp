#include "boardPanel.h"

void BoardPanel::resizeEvent(QResizeEvent *e)
{
    fitInView(this->scene()->sceneRect(), Qt::KeepAspectRatio);
}
