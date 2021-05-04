#include "gamefinishdialog.h"
#include "ui_gamefinishdialog.h"

GameFinishDialog::GameFinishDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameFinishDialog)
{
    ui->setupUi(this);
}

GameFinishDialog::~GameFinishDialog()
{
    delete ui;
}

void GameFinishDialog::setLabel(QString label) {
    ui->labelGameResult->setText(label);
}
