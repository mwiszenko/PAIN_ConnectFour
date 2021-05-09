import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
import QtQuick.Dialogs 1.2
import QtQuick.Particles 2.15

import "logic.js" as Logic

Window {
    id: app
    width: 350
    height: 480
    minimumHeight: 300
    minimumWidth: 300
    visible: true
    title: qsTr("Connect Four")
    property string playerOneName: "Player One"
    property string playerTwoName: "Player Two"
    property int currPlayer: 1

    property string arrowImg: "img/arrow_left.png"

    GridLayout {
        id: mainLayout
        anchors.fill: parent

        rows: 3

        Rectangle {
            Layout.row: 0
            Layout.fillWidth: true

            implicitWidth: app.width
            implicitHeight: app.height * 0.2

            id: playerBar

            Layout.margins: 10

            RowLayout {
                anchors.fill: parent

                ColumnLayout {
                    id: playerOneLayout
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Image {
                        id: playerOneImage
                        source: "img/red_player.png"
                        antialiasing: true
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        fillMode: Image.PreserveAspectFit
                    }

                    Label {
                        id: playerOneLabel
                        font.bold: true
                        text: app.playerOneName
                        horizontalAlignment: Text.AlignHCenter
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    }
                }

                Image {
                    id: arrow
                    source: app.arrowImg
                    antialiasing: true
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    fillMode: Image.PreserveAspectFit

                }

                ColumnLayout {
                    id: playerTwoLayout
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Image {
                        id: playerTwoImage
                        source: "img/blue_player.png"
                        antialiasing: true
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        fillMode: Image.PreserveAspectFit
                    }

                    Label {
                        id: playerTwoLabel
                        font.bold: true
                        text: app.playerTwoName
                        horizontalAlignment: Text.AlignHCenter
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }
                }
            }
        }

        Grid {
            Layout.row: 1
            Layout.fillWidth: true
            Layout.fillHeight: true

            id: board

            rows: 6
            columns: 7
            spacing: 5
            anchors.margins: 5
            antialiasing: true
            Layout.margins: 10

            property real buttonWidth: (width - (columns - 1) * spacing) / columns
            property real buttonHeight: (height - (rows - 1) * spacing) / rows

            Repeater {
                id: fields
                model: board.rows * board.columns

                Rectangle {
                    property int column: index % board.columns
                    property int row: index / board.columns
                    property bool available: row == board.rows - 1 ? true : false
                    property int idx: index
                    property string blockImg: ""
                    property int player: 0

                    id: field
                    color: available ? "green" : "lightgray"
                    clip: false

                    implicitWidth: board.buttonWidth
                    implicitHeight: board.buttonHeight

                    Image {
                        id: block
                        source: field.blockImg

                        height: field.height
                        antialiasing: true
                        width: field.width
                    }

                    MouseArea {
                        id: ma
                        anchors.fill: parent
                        onClicked: {
                            Logic.processClick(idx)
                        }
                    }
                }
            }
        }

        Rectangle {
            Layout.row: 2
            Layout.fillWidth: true

            implicitWidth: app.width
            implicitHeight: app.height * 0.1

            id: toolBar

            Layout.margins: 10

            RowLayout {
                anchors.fill: parent

                Button {
                    id: newGameButton
                    text: "New \nGame"

                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    onClicked: Logic.startNew()
                }

                Button {
                    id: settingsButton
                    text: "Settings"

                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    onClicked: {
                        settingsDialog.open()
                    }
                }

                Button {
                    id: creditsButton
                    text: "Credits"

                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    onClicked: {
                        creditsDialog.open()
                    }
                }

                Button {
                    id: exitButton
                    text: "Exit"

                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    onClicked: Qt.quit()
                }
            }
        }
    }

    Dialog {
        id: settingsDialog
        title: "Settings"
        standardButtons: StandardButton.Cancel | StandardButton.Ok

        onButtonClicked: {
            if(clickedButton === StandardButton.Ok) {
                app.playerOneName = playerOneNameTextInput.text
                app.playerTwoName = playerTwoNameTextInput.text
            }
        }

        ColumnLayout {
            width: parent.width

            Label {
                id: playerOneNameLabel
                text: "Player One Name:"
                color: "white"
                Layout.fillWidth: true
            }

            TextInput {
                id: playerOneNameTextInput
                text: app.playerOneName
                Layout.fillWidth: true
            }

            Label {
                id: playerTwoNameLabel
                text: "Player Two Name:"
                color: "white"
                Layout.fillWidth: true
            }

            TextInput {
                id: playerTwoNameTextInput
                text: app.playerTwoName
                Layout.fillWidth: true
            }
        }
    }

    Dialog {
        id: gameFinishedDialog
        title: "Game Finished"
        property string message: ""

        Label {
            text: gameFinishedDialog.message
            color: "white"
            horizontalAlignment: Text.AlignLeft
            Layout.fillWidth: true
        }
    }

    Dialog {
        id: creditsDialog
        title: "Credits"

        GridLayout {
            width: parent.width
            rows: 5
            columns: 2

            Label {
                text: app.playerOneName
                color: "white"
                horizontalAlignment: Label.AlignLeft
                Layout.fillWidth: true
            }

            Label {
                text: "Game Over!\nYou did your best!"
                horizontalAlignment: Label.AlignLeft
                Layout.fillWidth: true
            }
        }
    }
}
