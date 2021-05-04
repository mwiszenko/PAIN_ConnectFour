#include <QtGui>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "board.h"
#include "game.h"
#include "constants.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    settings = new SettingsDialog();

    gameFinishDialog = new GameFinishDialog();

    setupActions();

    setupGame();

    connect(settings, &SettingsDialog::settingsChanged, game, &Game::settingsChanged);
    connect(settings, &SettingsDialog::settingsChanged, this, &MainWindow::settingsChanged);

    ui->labelPlayerOneImage->setPixmap(QPixmap(":/img/red_circle.png"));
    ui->labelPlayerOneName->setText("Player 1");

    ui->labelPlayerTwoImage->setPixmap(QPixmap(":/img/blue_circle.png"));
    ui->labelPlayerTwoName->setText("Player 2");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupActions()
{
    connect(ui->actionNewGame, SIGNAL(triggered()), this, SLOT(newGame()));
    connect(ui->actionSettings, SIGNAL(triggered()), this, SLOT(showSettings()));
    connect(ui->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::setupGame() {
    game = new Game();
    this->boardPanel = new BoardPanel(this);
    this->boardPanel->setScene(game->board);
    ui->gameLayout->addWidget(boardPanel);
    ui->labelArrow->setPixmap(QPixmap(":/img/arrow_up.png"));
    connect(game, &Game::gameEnded, this, &MainWindow::processGameWon);
    connect(game, &Game::nextTurn, this, &MainWindow::processNextTurn);
}

void MainWindow::showSettings()
{
    settings->show();
}

void MainWindow::newGame() {
    game->newGame();
    this->boardPanel->setScene(game->board);
    ui->labelArrow->setPixmap(QPixmap(":/img/arrow_up.png"));
}

void MainWindow::processNextTurn(int player) {
    if(player == 1) {
        ui->labelArrow->setPixmap(QPixmap(":/img/arrow_up.png"));
    } else if (player == 2) {
        ui->labelArrow->setPixmap(QPixmap(":/img/arrow_down.png"));
    } else {
        ui->labelArrow->setPixmap(QPixmap(":/img/dash.png"));
    }
}

void MainWindow::processGameWon(int result) {
    if (result == 0) {
        gameFinishDialog->setLabel(QString("It's a draw..."));
    } else if (result == 1) {
        gameFinishDialog->setLabel(QString(ui->labelPlayerOneName->text() + " has won!"));
    } else if (result == 2) {
        gameFinishDialog->setLabel(QString(ui->labelPlayerTwoName->text() + " has won!"));
    }
    gameFinishDialog->show();
}

void MainWindow::settingsChanged(QStringList settings) {
    ui->labelPlayerOneName->setText(settings[1]);
    ui->labelPlayerTwoName->setText(settings[2]);
}
