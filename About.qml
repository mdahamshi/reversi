import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.2
import QtQuick 2.7


Dialog{
    id: about
    visible: false
    title: "About"
    width: 640
    height: 650



    contentItem: Column{
        spacing: 20


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
                    about.visible = false
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
                anchors.rightMargin: 0
                toolTipText: "Click to zoom in"
                onButtonClicked: {
                    helpText.fontSize = helpText.fontSize + 1
                    names.fontSize = names.fontSize + 1
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
                     names.fontSize = names.fontSize - 1
                }
            }


        Text{
            id: helpText
            property alias fontSize: helpText.font.pointSize
            font.pointSize: 14
            textFormat: Text.StyledText
            leftPadding: 10
            horizontalAlignment: Text.AlignJustify
            text:"<h1>This game was built by:</h1><br/>"


        }
        Text{
            id: names
            property alias fontSize: names.font.pointSize
            font.pointSize: 14
            textFormat: Text.PlainText
            anchors.top: helpText.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            leftPadding: 10
            horizontalAlignment: Text.Center
            text:
            "Mohammad Dahamshi - mmd.0@hotmail.com\n"
            +"Naseem Hanna - naseem.hanna1@gmail.com \n"
            +"As homework by: Professor Larry Manevitz\n "
            +"All rights reserved®\n"


        }
        Row{
            anchors.top: names.bottom
            anchors.margins: 10
            width: parent.width

            Image {
                id: me
                width: parent.width / 2
                fillMode: Image.PreserveAspectFit
                source: "Res/me.jpg"
            }

            Image {
                id: ns
                width: parent.width / 2
                fillMode: Image.PreserveAspectFit
                source: "Res/ns.jpg"
            }
        }
        Text{
            font.pointSize: 14
            textFormat: Text.StyledText
            anchors.bottom: zoomout.top
            anchors.margins: 0
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignJustify
            text: "<h6>2016, MMD_CS™ ©</h6>"

        }





    }
}
