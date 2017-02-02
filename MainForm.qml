import QtQuick 2.5
import "game.js" as MyScript
import "singleton"

Rectangle {
    id: background

    property alias textEdit: textEdit
    anchors.fill: parent
    width: parent.width
    height: parent.height
    property alias start: start
    property alias help: help
    property alias image: image
    Item {
               id: gameCanvas

               property int score: 0
               property int blockSize: 40


               width: parent.width
               height: parent.height
               anchors.fill: parent
               Grid{
                   rows: MyScript.maxColumn; columns: MyScript.maxRow
                   id: gameBlocks
                   anchors.fill: parent
                   visible: false
                   width: parent.width
                   height: parent.height
                   enabled: false

                   Repeater{
                       model:myBroker.getBoardSize()
                       delegate: Block{

                       }

                   }


               }




           }

        Connections{
            target: myBroker
            onUpdateBoard: {
                MyScript.updateBoard();
                MyScript.unlockBoard();
                if(myBroker.getTurn() === MyStyle.whiteColor)
                    status.text = "White Turn";
                else
                    status.text = "Black Turn";
            }
            onYourTurn:{
                status.text = "Your turn !";
            }
            onGameRestart:{
                MyScript.updateBoard();
            }

            onGameEnd:{
                if (whiteCount.score > blackCount.score)
                    status.text = "White is the king !"
                if (whiteCount.score == blackCount.score)
                    status.text = "Both are kings !"
                if (whiteCount.score < blackCount.score)
                    status.text = "Black is king"
                MyScript.lockBoard();
            }
        }

        Image {
            id: image
            width: parent.width / 2
            height: parent.height / 2
            anchors.topMargin: 30
            anchors.centerIn: parent


            source: "Res/1.png"
        }

        MyButton {
            id: start
            color: "#80BBF7"
            anchors.top: image.bottom
            anchors.topMargin: 20
            anchors.horizontalCenter: image.horizontalCenter
            customText : "<b>Start</b>"
            fontSize: 22
            width: 100
            height: 80
            onButtonClicked:{
                gameSet.visible = true;

            }
            toolTipText: "Click to start the fun !"
        }

        Rectangle{
           id: whiteScore
           anchors.bottom: parent.bottom
           anchors.left: about.right
           anchors.margins: 5
           anchors.leftMargin: 50
           width: 40;height: 40
           radius: width / 2
           border.color: "black"
           border.width: 1
           color: "white"
           visible: false


        }
         Rectangle{
           id: blackScore
           visible: false
           radius: width / 2
           anchors.bottom: parent.bottom
           anchors.right: quit.left
           anchors.rightMargin: 50
           anchors.margins: 5
           width: 40;height: 40
           color: "black"

        }
         Text {
             id: blackCount
             property int score: 2
             text: qsTr(score+" x")
             visible: false
             anchors.bottom: parent.bottom
             anchors.bottomMargin: 8
             anchors.right: blackScore.left
             anchors.rightMargin: 10
             font.pointSize: 20
         }
          Text {
             id: whiteCount
             property int score: 2
             text: qsTr("x "+score)
             visible: false
             anchors.bottomMargin: 8
             anchors.bottom: parent.bottom
             anchors.leftMargin: 10
             anchors.left: whiteScore.right
             font.pointSize: 20
         }

       MyButton{
            id: help
            color: "#80BBF7"
            anchors.bottom: background.bottom
            anchors.topMargin: 20
            anchors.horizontalCenter: start.horizontalCenter

            customText: "Help"
            width: 100; height: 50
            onButtonClicked: {
                myHelp.visible = true
            }
            toolTipText: "Click to show you instructions"

        }
       Text {
           id: status
           text: qsTr("Hello")
           font.pointSize: 20
           visible: false
           anchors.bottom: help.top
           anchors.bottomMargin: 10
           anchors.horizontalCenter: help.horizontalCenter
       }

       MyButton{
           id: quit

           anchors.bottom: parent.bottom
           anchors.right: parent.right
           anchors.margins: 5
           width: 40;height: 40
           color: "red"
           customText: "X"
           fontSize: 20
           onButtonClicked: {

               exitDialog.visible = true
           }

           toolTipText: "Click to quit or restart the game"
        }
       MyButton{
           id: about
           anchors.bottom: parent.bottom
           anchors.left: parent.left
           anchors.margins: 5
           width: 40;height: 40
           color: "green"
           customText: "?"
           fontSize: 20
           onButtonClicked: myAbout.visible = true
           toolTipText: "Click to show About"

        }
       About{
            id:myAbout
       }

        Help{
            id:myHelp
        }
        GameSetting{
            id:gameSet
        }
        ExitDialog{
            id:exitDialog
        }




    TextEdit {
        id: textEdit
        text: qsTr("Hello , Please hit start")
        font.pointSize: 24

        verticalAlignment: Text.AlignVCenter
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 50
        Rectangle {
            anchors.fill: parent
            anchors.margins: -10
            color: "transparent"
            border.width: 3
        }
    }
    Component.onCompleted: {
        MyScript.unlockBoard();
        MyScript.updateBoard();
    }
}
