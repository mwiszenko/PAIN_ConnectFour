#ifndef CREDITSDIALOG_H
#define CREDITSDIALOG_H

#include <QDialog>
#include <QVector>
#include <QAbstractButton>

namespace Ui {
class CreditsDialog;
}

class CreditsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreditsDialog(QWidget *parent = nullptr);
    ~CreditsDialog();
    void setLabel(QString);

private:
    Ui::CreditsDialog *ui;
};

#endif // CREDITSDIALOG_H
