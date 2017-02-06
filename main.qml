import QtQuick 2.5
import QtQuick.Window 2.2
import "game.js" as MyScript
import "singleton"
import reversi 1.0

Window {
    visible: true
    width: 600
    height: 600 + 100
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width
    title: qsTr("Reversi , Professor Larry Manevitz  Edition")

    MainForm {
        anchors.fill: parent
        id: mainF

    }

}
