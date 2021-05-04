#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QVector>
#include <QAbstractButton>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

    QString animationSpeed();
    QString playerOneName();
    QString playerTwoName();


signals:
    void settingsChanged(QStringList settings);

private slots:
    void buttonClicked(QAbstractButton *button);

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
