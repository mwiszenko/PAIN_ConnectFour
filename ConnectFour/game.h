#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "constants.h"

class Game : public QObject
{
    Q_OBJECT

public:
    Board* board;
    Game();
    void newGame();

public slots:
    void processClick(int, int);
    void settingsChanged(QStringList);
    void setFieldsNoninteractive();
    void setFieldsInteractive();

private:
    int animationSpeed;
    int currentPlayer;
    bool verticalCheck(int);
    bool horizontalCheck(int);
    bool descendingDiagonalCheck(int);
    bool ascendingDiagonalCheck(int);
    bool hasGameFinished(int);
    bool hasGameBeenDrawn();
    void setFieldAvailability(int, int);

signals:
    void gameEnded(int);
    void nextTurn(int);
};

#endif // GAME_H
