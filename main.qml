import QtQuick 2.5
import QtQuick.Window 2.2
import "game.js" as MyScript
import "singleton"
import reversi 1.0

Window {
    visible: true
    width: MyScript.maxColumn * MyScript.blockSize
    height: MyScript.maxRow * MyScript.blockSize + 50
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width
    title: qsTr("Reversi , Dr. Larry Manevitz  Edition")

    MainForm {
        anchors.fill: parent
        id: mainF

    }

}
