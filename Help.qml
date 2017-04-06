import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.2
import QtQuick 2.7


Dialog{
    id: help
    visible: false
    title: "Help"
    width: 640
    height: 640


    contentItem: Column{

            MyButton{
                id: ret
                width: 100
                height: 50
                customText: "return"
                z:2
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.rightMargin: 20
                onButtonClicked: {
                    help.visible = false
                }
                toolTipText: "Click to return to Home"
            }
            MyButton{
                id: zoomin
                width: 50
                height: 50
                customText: "+"
                z:2
                anchors.right: parent.right
                anchors.bottom: ret.bottom
                anchors.rightMargin: 18
                toolTipText: "Click to zoom in"
                onButtonClicked: {
                    helpText.fontSize = helpText.fontSize + 1
                }
            }
            MyButton{
                id: zoomout
                width: 50
                height: 50
                customText: "-"
                z:2
                anchors.left: parent.left
                anchors.bottom: ret.bottom
                anchors.rightMargin: 20
                toolTipText: "Click to zoom out"
                onButtonClicked: {
                    helpText.fontSize = helpText.fontSize - 1
                }
            }




        TextArea {
            id: helpText
            property alias fontSize: helpText.font.pointSize
            width: parent.width
            height: parent.height
            textFormat: TextEdit.RichText
            textMargin: 10
            horizontalAlignment: Text.AlignJustify
            readOnly: true
            font.pointSize: 13
            anchors.centerIn: parent
            wrapMode: Text.WordWrap
            text: qsTr("<b>About Othello</b><br/>
Othello is the trading name of a much older board game, Reversi. In both its originally named form and the newer trademark this game has become very popular on computers as much as in board format. Often referred to as a game of abstract strategy, Othello can only be played as a 2 player game. Made up of 8 rows and 8 columns, the board is populated with pieces from both players in turn. Each player’s pieces will be of one colour with the most common occurrence being black and white.
<br/><br/><b>How to Play Othello</b><br/>
Players battle to finish the game with more of their own pieces on the board than their opponent. The game is classed as finished when there are no spaces left on the board or there are no more possible legal moves for either competitor
<br/><br/><b>The Start</b><br/>
Both players begin the game with two pieces on the board in the four centre squares. No two matching colours are connected vertically or horizontally so a miniature chequered pattern is made. In the typical set ups where it is black versus white the person using black chips must make the first move.
<br/><br/><b>The Game</b><br/>
Both players take it in turns to make their move which consists of placing one piece down in a legally acceptable position and then turning any of the opposing player’s pieces where applicable. A legal move is one that consists of, for example, a black piece being placed on the board that creates a straight line (vertical, horizontal or diagonal) made up of a black piece at either end and only white pieces in between. When a player achieves this, they must complete the move by turning any white pieces in between the two black so that they line becomes entirely black. This turning action must be completed for every legal turning line that is created with the placing of the new piece.
It goes without say that while the example assumes the use of black as the moving player, it is applicable both ways.
Players will then continue to move alternately until they get to the end of the game and a winner is decided. This decision is reached by identifying which of the two opponents has the most pieces on the board.
<br/><br/><b>Timing</b><br/>
For stricter or regulated games there is an alternative method of finishing a game. Players can start with a preset time limit for their total number of moves. The clock will start counting down at the beginning of a player’s first move and be paused each time they complete a turn whilst the opposing player’s clock is ticking down. There are varying time limits ranging from one minute for coffee break style desktop versions right up to thirty minutes as seen in the world championship rules and regulations.
This timing element adds more pressure to the game and forces players to exercise not only a logical approach but also a concise and sharply reactive one. This is because in the event that one player’s clock runs out of time, no matter what the position or number of chips on the board, the player with no time left has no choice but to forfeit the game and therefore lose.<br/><br/><br/><br/><br/><br/>")

        }

    }
}
