import PuzzleFunctions

def getBoardManhattanScore(board, successBoard):
    manhattanSum = 0

    for i in range(0, len(board)):
        for k in range(0, len(board[i])):
            otherTileI, otherTileK = PuzzleFunctions.findTileWithValue(successBoard, board[i][k])
            manhattanDiff = abs(otherTileI-i)+abs(otherTileK-k)
            manhattanSum = manhattanSum+manhattanDiff

    return manhattanSum

def getNumMispacedTiles(board, successBoard):
    
    displacedCount = 0

    for i in range(0, len(board)):
        for k in range(0, len(board[i])):
            otherTileI, otherTileK = PuzzleFunctions.findTileWithValue(successBoard, board[i][k])
            if(i != otherTileI and k != otherTileK):
                displacedCount = displacedCount+1

    return displacedCount

    