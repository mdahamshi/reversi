import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.2
import QtQuick 2.7


Dialog{
    id: exit
    visible: false
    title: "Exit"
    width: 500
    height: 300




    contentItem: Column{
        spacing: 20


            MyButton{
                id: ret
                width: 100
                height: 50
                customText: "return"
                z:2
                anchors.right: exitgame.left
                anchors.bottom: exitgame.bottom
                anchors.rightMargin: 80
                onButtonClicked: {
                    exit.visible = false
                }
                toolTipText: "Click to return to game"
            }
            MyButton{
                id: restart
                width: 100
                height: 50
                customText: "restart"
                visible: false
                z:2
                color:"green"
                anchors.left:  parent.left
                y: parent.height / 2
                anchors.leftMargin:  20
                toolTipText: "Click to restart the game"
                onButtonClicked: {
                    myBroker.endCurrentGame();
                }

            }
            Connections{
                target: myBroker
                onGameStart :{
                    restart.visible = true
                }
                onGameEnd:{
                    restart.visible = true
                }
                onGameRestart:{
                    exitDialog.visible = false
                    restart.visible = false
                    gameSet.visible = true
                    gameBlocks.visible = false
                    whiteScore.visible = false
                    blackScore.visible = false
                    blackCount.visible = false
                    whiteCount.visible = false

                    status.visible = false
                    status.text = "Hello"
                    background.image.visible = true;
                    background.start.visible = true;
                    background.textEdit.visible = true;

                }
            }
            MyButton{
                id: exitgame
                width: 100
                height: 50
                color: "red"
                customText: "Exit"
                z:2
                anchors.right:  parent.right
                y: parent.height / 2
                anchors.rightMargin: 20
                toolTipText: "Click to exit the game"
                onButtonClicked: {
                     Qt.quit()
                }
            }

        Text{
            id: helpText
            property alias fontSize: helpText.font.pointSize
            font.pointSize: 14
            textFormat: Text.StyledText
            leftPadding: 10
            horizontalAlignment: Text.AlignJustify
            text:"<h1>Please confirm: </h1><br/>"


        }





    }
}

