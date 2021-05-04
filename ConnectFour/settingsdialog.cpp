#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::clicked, this, &SettingsDialog::buttonClicked);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

QString SettingsDialog::animationSpeed()
{
    return QString::number(ui->comboBoxAnimationSpeed->currentIndex());
}

QString SettingsDialog::playerOneName()
{
    return QString(ui->lineEditPlayerOneName->text());
}

QString SettingsDialog::playerTwoName()
{
    return QString(ui->lineEditPlayerTwoName->text());
}

void SettingsDialog::buttonClicked(QAbstractButton *button) {
    if(button->text() == "OK") {
        QStringList settings;
        settings.append(animationSpeed());
        settings.append(playerOneName());
        settings.append(playerTwoName());
        emit settingsChanged(settings);
    }
}
