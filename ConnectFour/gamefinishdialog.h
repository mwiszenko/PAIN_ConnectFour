#ifndef GAMEFINISHDIALOG_H
#define GAMEFINISHDIALOG_H

#include <QDialog>
#include <QVector>
#include <QAbstractButton>

namespace Ui {
class GameFinishDialog;
}

class GameFinishDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameFinishDialog(QWidget *parent = nullptr);
    ~GameFinishDialog();
    void setLabel(QString);

private:
    Ui::GameFinishDialog *ui;
};

#endif // GAMEFINISHDIALOG_H
