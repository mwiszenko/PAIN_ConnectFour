#include "boardpanel.h"

void BoardPanel::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);
    fitInView(this->scene()->sceneRect(), Qt::KeepAspectRatio);
}
