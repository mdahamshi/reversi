import QtQuick 2.5
import "game.js" as MyScript

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

                   Repeater{
                       model:myBroker.getBoardSize()
                       delegate: Block{

                       }

                   }


               }




           }

        Connections{
            target: myBroker
            onUpdateBoard: MyScript.updateBoard()
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
                gameBlocks.visible = true
                whiteScore.visible = true
                blackScore.visible = true
                blackCount.visible = true
                whiteCount.visible = true
                background.image.visible = false;
                background.start.visible = false;
                background.textEdit.visible = false;
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

       MyButton{
           id: quit
           anchors.bottom: parent.bottom
           anchors.right: parent.right
           anchors.margins: 5
           width: 40;height: 40
           color: "red"
           customText: "X"
           fontSize: 20
           onButtonClicked: Qt.quit()
           toolTipText: "Click to quit"
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
    Component.onCompleted: MyScript.updateBoard()
}
