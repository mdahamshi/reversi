import QtQuick 2.0
import QtQuick.Dialogs 1.2

import QtQuick.Controls 2.0
Dialog{
    id: gameset
    visible: false
    title: "Game Settings"
    width: 640
    height: 650


    function getBlackAlgo(){
        if (blacktypebutton.checkedButton.playertype === 0)
            return 0;
        else
            return blackalgo.checkedButton.alg
    }
    function getWhiteAlgo(){
        if (whitetypebutton.checkedButton.playertype === 0)
            return 0;
        else
            return whitealgo.checkedButton.alg
    }
    function getWhiteDep(){
        if (whitetypebutton.checkedButton.playertype === 0)
            return 0;
        else
            return whitedepthMenu.currentIndex +1;
    }
    function getBlackDep(){
        if (blacktypebutton.checkedButton.playertype === 0)
            return 0;
        else
            return blackdepthMenu.currentIndex +1;
    }


    contentItem: Column{
        spacing: 20



        Text {
                    id: blackp
                    text: qsTr("<h1>Black player:<h1/> ")

                    anchors.bottom: blackdepthRow.top
                    anchors.bottomMargin: 20
                    x:30
                }

        Row{
            id:blackdepthRow
            x:parent.width /2- 100
            y:100

            Text {
                id: blackdepthText
                text: qsTr("AI Black Depth: ")
                anchors.centerIn: parent
            }
            ComboBox {
                id:blackdepthMenu
                width: 200
                enabled: false
                model: [ "1", "2", "3","4","5","6","7","8","9","10" ]
                anchors.left: blackdepthText.right
                anchors.baseline: blackdepthText.bottom

            }
        }
        ButtonGroup { id: blacktypebutton }

                Column {
                    id:blackplayertype
                    anchors.top: blackdepthRow.bottom
                    anchors.topMargin: 30
                    anchors.left: blackdepthRow.left
                    Label {
                        text: qsTr("Player type:")
                    }

                    RadioButton {
                        checked: true
                        text: qsTr("Human")
                        ButtonGroup.group: blacktypebutton
                        property int playertype: 0

                    }

                    RadioButton {
                        text: qsTr("PC")
                        ButtonGroup.group: blacktypebutton
                        property int playertype: 1
                        onClicked: {
                            blackdepthMenu.enabled = true
                            blackalgoCol.visible = true
                        }

                        onCheckedChanged: {
                            blackdepthMenu.enabled = false
                            blackalgoCol.visible = false
                        }

                    }
                }
                ButtonGroup { id: blackalgo }
                        Column {
                            id: blackalgoCol
                            visible: false
                            anchors.left: blackplayertype.left
                           anchors.top:blackplayertype.bottom
                            Label {
                                text: qsTr("Algorithm:")
                            }

                            RadioButton {
                                checked: true
                                text: qsTr("minimax")
                                ButtonGroup.group: blackalgo
                                property int alg: 1
                            }

                            RadioButton {
                                text: qsTr("alpha-beta")
                                ButtonGroup.group: blackalgo
                                property int alg: 2

                            }


                        }

                Text {
                            id: whitep
                            text: qsTr("<h1>White player:<h1/> ")

                            anchors.top: blackalgoCol.bottom
                            anchors.bottomMargin: 20
                            x:30
                        }
                Row{
                            id:whitedepthRow
                            x:parent.width /2- 100
                            anchors.top: whitep.bottom

                        Text {
                            id: whitedepthText
                            text: qsTr("AI White Depth: ")
                            anchors.centerIn: parent
                        }
                        ComboBox {
                            id:whitedepthMenu
                            width: 200
                            enabled: false
                            model: [ "1", "2", "3","4","5","6","7","8","9","10" ]
                            anchors.left: whitedepthText.right
                            anchors.baseline: whitedepthText.bottom


                        }
                }

                ButtonGroup { id: whitetypebutton }

                        Column {
                            id:whiteplayertype
                            anchors.top: whitedepthRow.bottom
                            anchors.left: whitedepthRow.left
                            anchors.topMargin: 30
                            Label {
                                text: qsTr("Player type:")
                            }

                            RadioButton {
                                checked: true
                                text: qsTr("Human")
                                ButtonGroup.group: whitetypebutton
                                property int playertype: 0

                            }

                            RadioButton {
                                text: qsTr("PC")
                                ButtonGroup.group: whitetypebutton
                                property int playertype: 1
                                onClicked: {
                                    whitedepthMenu.enabled = true
                                    whitealgoCol.visible = true
                                }

                                onCheckedChanged: {
                                    whitedepthMenu.enabled = false
                                    whitealgoCol.visible = false
                                }

                            }
                        }

                        ButtonGroup { id: whitealgo }
                                Column {
                                    id: whitealgoCol
                                    visible: false
                                    anchors.left: whiteplayertype.left
                                   anchors.top:whiteplayertype.bottom
                                    Label {
                                        text: qsTr("Algorithm:")
                                    }

                                    RadioButton {
                                        checked: true
                                        text: qsTr("minimax")
                                        ButtonGroup.group: whitealgo
                                        property int alg: 1
                                    }

                                    RadioButton {
                                        text: qsTr("alpha-beta")
                                        ButtonGroup.group: whitealgo
                                        property int alg: 2

                                    }


                                }

                MyButton{
                                id: ret
                                width: 100
                                height: 50
                                customText: "return"
                                z:2
                                anchors.right: begin.left
                                anchors.rightMargin: 40
                                anchors.bottom: parent.bottom

                                onButtonClicked: {
                                    gameset.visible = false
                                }
                                toolTipText: "Click to return"
                            }
                            MyButton{
                                id: begin
                                width: 100
                                height: 50
                                customText: "begin"
                                z:2
                                x:gameset.width / 2 + 25
                                anchors.bottom: parent.bottom
                                toolTipText: "Click to begin the game"
                                onButtonClicked: {
                                    gameBlocks.visible = true
                                    whiteScore.visible = true
                                    blackScore.visible = true
                                    blackCount.visible = true
                                    whiteCount.visible = true
                                    gameset.visible = false
                                    status.visible = true
                                    background.image.visible = false;
                                    background.start.visible = false;
                                    background.textEdit.visible = false;

                                    myBroker.createGame(blacktypebutton.checkedButton.playertype,
                                                       whitetypebutton.checkedButton.playertype,
                                                        getBlackAlgo(),
                                                        getWhiteAlgo(),
                                                        getBlackDep(),
                                                        getWhiteDep());
                                    console.log("finished creating game !");
                                }
                            }







    }
}
