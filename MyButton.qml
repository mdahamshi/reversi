import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    id: rec
    width: 100; height: 100
    color: "#80BBF7"
    property string customText: "hh"
    property int fontSize: 14
    property string toolTipText: "click me !"
    property color oldColor: "#ffffff"

     signal buttonClicked()
    Text {
        id: name
        text: qsTr(customText)
        font.pointSize: fontSize
        verticalAlignment: Text.AlignVCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

    }
    MouseArea {
        id: mouseArea
        hoverEnabled: true
        anchors.fill: parent
        onClicked: console.log("Button clicked!"),buttonClicked()
        ToolTip{
            id:toolTip

            text:toolTipText
        }
        onEntered:{
            oldColor = rec.color
            rec.color = Qt.lighter( rec.color,1.2)
            toolTip.visible = true
        }
        onExited: {
             rec.color = oldColor
            toolTip.visible = false
        }
    }
}
