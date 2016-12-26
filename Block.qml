import QtQuick 2.0
import "game.js" as MyScript
import "singleton"
Item {
    id: block
    width: 50
    height: 50

    property int type: 0
//    property string blockImageS:   "Res/blank2.png"
    property alias myBlockImage:  blockImage
    Image {
        id: blockImage
        anchors.fill: parent
        source: "Res/blank2.png"

    }
    function changeColor(color){
        if (color == MyStyle.whiteColor){
            blockArea.old = MyStyle.whiteDir
            blockImage.source = MyStyle.whiteDir
            type = MyStyle.whiteColor
        }
        else if (color == MyStyle.blackColor){
            blockArea.old = MyStyle.blackDir
            blockImage.source = MyStyle.blackDir
            type = MyStyle.blackColor
        }
        else{
            blockArea.old = MyStyle.blankDir
            blockImage.source = MyStyle.blankDir
            type = MyStyle.blankColor
        }


    }


    MouseArea{
        id: blockArea
        anchors.fill: parent
        hoverEnabled: true
        property string old: blockImage.source+""
        onEntered: {
            if(type == MyStyle.blankColor){
                old = blockImage.source+""
                blockImage.source= MyStyle.activeDir
                blockImage.sourceChanged(blockImage.source)
            }

        }
        onExited: {
            if(type == MyStyle.blankColor){
                blockImage.source= old
                blockImage.sourceChanged(blockImage.source)
                console.log(qsTr('hovered exit'+type+old))
            }

       }
        onClicked: {
       {
                if(block.type == MyStyle.blankColor){

                    block.changeColor( MyStyle.whiteColor)
                    blockImage.sourceChanged(blockImage.source)
                    console.log(qsTr('blockChanged'+type))
                }
                console.log(qsTr(""+type))
            }
        }
    }
}
