function processClick(idx) {
    if(fields.itemAt(idx).available) {
        fields.itemAt(idx).available = false
        fields.itemAt(idx).player = currPlayer
        if(currPlayer === 1) {
            fields.itemAt(idx).blockImg = "img/red_block.png"
        } else {
            fields.itemAt(idx).blockImg = "img/blue_block.png"
        }
        let gameStatus = hasGameFinished()
        if(gameStatus === 0) {
            setAllFieldsUnavailable()
            arrowImg = "img/dash.png"
            gameFinishedDialog.message = "It's a draw..."
            gameFinishedDialog.open()
            return
        } else if(gameStatus === 1) {
            setAllFieldsUnavailable()
            arrowImg = "img/dash.png"
            gameFinishedDialog.message = playerOneName + " won!"
            gameFinishedDialog.open()
            return
        } else if(gameStatus === 2) {
            setAllFieldsUnavailable()
            arrowImg = "img/dash.png"
            gameFinishedDialog.message = playerTwoName + " won!"
            gameFinishedDialog.open()
            return
        }
        if(currPlayer === 1) {
            currPlayer = 2
            arrowImg = "img/arrow_right.png"
        } else {
            currPlayer = 1
            arrowImg = "img/arrow_left.png"
        }
        if(fields.itemAt(idx).row !== 0) {
            fields.itemAt(idx - board.columns).available = true
        }
    }
}

function hasGameFinished() {
    if(verticalCheck() || horizontalCheck() || ascendingDiagonalCheck() || descendingDiagonalCheck()) {
        return currPlayer;
    }
    if(hasGameBeenDrawn(board)) {
        return 0
    }
    return -1;
}

function hasGameBeenDrawn() {
    for(var i = 0; i < fields.count; i++) {
        if(fields.itemAt(i).available === true) {
            return false
        }
    }
    return true;
}

function verticalCheck() {
    for(var i = 0; i < fields.count - 3 * board.columns; i++) {
        if (fields.itemAt(i).player === currPlayer && fields.itemAt(i + board.columns).player === currPlayer
                && fields.itemAt(i + 2 * board.columns).player === currPlayer && fields.itemAt(i + 3 * board.columns).player === currPlayer) {
            return true;
        }
    }
}

function horizontalCheck() {
    for(var i = 0; i < fields.count; i++) {
        if(i % board.columns !== 6 && i % board.columns !== 5 && i % board.columns !== 4) {
            if (fields.itemAt(i).player === currPlayer && fields.itemAt(i + 1).player === currPlayer
                    && fields.itemAt(i + 2).player === currPlayer && fields.itemAt(i + 3).player === currPlayer) {
                return true;
            }
        }
    }
}

function ascendingDiagonalCheck() {
    for (var i = 0; i < fields.count; ++i) {
        if(i % board.columns !== 6 && i % board.columns !== 5 && i % board.columns !== 4) {
            if (fields.itemAt(i).player === currPlayer && fields.itemAt(i - board.columns + 1).player === currPlayer
                    && fields.itemAt(i - 2 * board.columns + 2).player === currPlayer  && fields.itemAt(i - 3 * board.columns + 3).player === currPlayer) {
                return true;
            }
        }
    }
    return false;
}

function descendingDiagonalCheck() {
    for (var i = 0; i < fields.count - 3 * board.columns; ++i) {
        if(i % board.columns !== 0 && i % board.columns !== 1 && i % board.columns !== 2) {
            if (fields.itemAt(i).player === currPlayer && fields.itemAt(i - board.columns - 1).player === currPlayer
                    && fields.itemAt(i - 2 * board.columns - 2).player === currPlayer  && fields.itemAt(i - 3 * board.columns - 3).player === currPlayer) {
                return true;
            }
        }
    }
    return false;
}

function setAllFieldsUnavailable() {
    for (var i = 0; i < fields.count; ++i) {
        fields.itemAt(i).available = false
    }
}

function startNew() {
    for (var i = 0; i < fields.count; ++i) {
        if(fields.itemAt(i).row === board.rows - 1) {
            fields.itemAt(i).available = true
        } else {
            fields.itemAt(i).available = false
        }
        fields.itemAt(i).player = 0
        fields.itemAt(i).blockImg = ""
    }
    currPlayer = 1
    arrowImg = "img/arrow_left.png"
}
