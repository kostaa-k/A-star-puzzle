import PuzzleFunctions

def getBoardManhattanScore(board, successBoard):
    #Defined as h1
    manhattanSum = 0

    for i in range(0, len(board)):
        for k in range(0, len(board[i])):
            otherTileI, otherTileK = PuzzleFunctions.findTileWithValue(successBoard, board[i][k])
            manhattanDiff = abs(otherTileI-i)+abs(otherTileK-k)
            manhattanSum = manhattanSum+manhattanDiff

    return manhattanSum

def getNumMispacedTiles(board, successBoard):
    #Defined as h2
    displacedCount = 0

    for i in range(0, len(board)):
        for k in range(0, len(board[i])):
            otherTileI, otherTileK = PuzzleFunctions.findTileWithValue(successBoard, board[i][k])
            if(i != otherTileI or k != otherTileK):
                displacedCount = displacedCount+1

    return displacedCount