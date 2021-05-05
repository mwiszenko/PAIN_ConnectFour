#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include "settingsdialog.h"
#include "gamefinishdialog.h"
#include "creditsdialog.h"
#include "game.h"
#include "boardpanel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void setupActions();
    void setupGame();
    void showSettings();
    void showCredits();
    void newGame();
    void processGameWon(int);
    void settingsChanged(QStringList);
    void processNextTurn(int);

private:
    Ui::MainWindow *ui;
    SettingsDialog *settingsDialog;
    GameFinishDialog* gameFinishDialog;
    CreditsDialog* creditsDialog;
    BoardPanel *boardPanel;
    Game* game;
};
#endif // MAINWINDOW_H
