var blockSize = 50;
var maxColumn = 12;
var maxRow = 12;
var maxIndex = maxColumn * maxRow;
var board = new Array(maxIndex);
var component;
var  colorEnum={
    BLANK:0,
    WHITE:1,
    BLACK:2

}

//Index function used instead of a 2D array
function index(column, row) {
    return column + (row * maxColumn);
}


function updateBoard() {

    for (var column = 0; column < maxColumn; column++) {
        for (var row = 0; row < maxRow; row++) {
            (gameBlocks.children[index(column, row)]).changeColor(row,column);

        }
    }
    blackCount.score = myBroker.getBlackCount();
    whiteCount.score = myBroker.getWhiteCount();


}


    function lockBoard(){
    gameBlocks.enabled = false;
    }
    function unlockBoard(){
    gameBlocks.enabled = true;;
    }
