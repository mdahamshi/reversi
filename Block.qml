import QtQuick 2.0
import QtQuick.Controls 2.0
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


    function changeColor(i,j){
    var color = myBroker.getColor(i,j);
        if (color != type){
            if (color  == MyStyle.whiteColor){
                blockArea.old = MyStyle.whiteDir
                blockImage.source = MyStyle.whiteDir
                type = MyStyle.whiteColor
            }
            else if (color == MyStyle.blackColor){
                blockArea.old = MyStyle.blackDir
                blockImage.source = MyStyle.blackDir
                type = MyStyle.blackColor
            }
            else if(color == MyStyle.possibleColor){
                blockArea.old = MyStyle.possibleDir
                blockImage.source = MyStyle.possibleDir
                type = MyStyle.possibleColor
            }
            else{
                blockArea.old = MyStyle.blankDir
                blockImage.source = MyStyle.blankDir
                type = MyStyle.blankColor
            }
              blockImage.sourceChanged(blockImage.source);
        }




    }


    MouseArea{
        id: blockArea
        anchors.fill: parent
        hoverEnabled: true
        property string old: blockImage.source+""
        property string cord: Math.floor(block.y / (block.height))+""+", "+Math.floor(block.x / (block.width))+""

        ToolTip{
            id:toolTip

            text:blockArea.cord
        }

        onEntered: {
            if(gameBlocks.enabled == true)
            if(type == MyStyle.blankColor || type == MyStyle.possibleColor ){
                old = blockImage.source+""
                blockImage.source= MyStyle.activeDir
                blockImage.sourceChanged(blockImage.source)
                toolTip.visible = true
            }

        }
        onExited: {
            if(gameBlocks.enabled == true)
            if(type == MyStyle.blankColor || type == MyStyle.possibleColor ){
                blockImage.source= old
                blockImage.sourceChanged(blockImage.source)
                toolTip.visible = false
            }

       }
        signal blockClickedAt(int i ,int j)
        onClicked: {
            status.text = "";
            console.log(Math.floor(block.x / (block.height)));
            if(block.type != MyStyle.possibleColor){
                status.text = "Wrong Choice !";
                status.color = "red";
            }
            else{
                MyScript.lockBoard();

                myBroker.gotInput(Math.floor(block.y / (block.height)),Math.floor(block.x / (block.width)));
            }

        }
    }
}
