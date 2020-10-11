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


#YOUR IMPLEMENTATIONS BELOW: :)


def getNumberOfIncompleteRowsAndCols(board, successBoard):

    rowCount = 0
    for i in range(0, len(board)):
        if(board[i] != successBoard[i]):
            rowCount = rowCount+1

    colCount = 0
    boardZipped = (list)(zip(*board))
    successZipped = (list)(zip(*successBoard))

    for i in range(0, len(boardZipped)):
        if(boardZipped[i] != successZipped[i]):
            colCount = colCount+1


    return rowCount+colCount


def getNumIncorrectRelatives(board, successBoard, add_to_max=True):

    maxValue = PuzzleFunctions.getMaxValue(board)+1
    countMisplaced = 0

    #Create padded board
    paddedBoard = PuzzleFunctions.createEmptyBoard(boardSize=len(board)+2)

    #Create padded success board
    paddedSuccessBoard = PuzzleFunctions.createEmptyBoard(boardSize=len(board)+2)

    #Fill both padded boards
    for i in range(0, len(paddedBoard)):
        for k in range(0, len(paddedBoard[i])):
            if(i == 0 or k == 0 or i == (len(paddedBoard)-1) or k == (len(paddedBoard)-1)):
                paddedBoard[i][k] = maxValue
                paddedSuccessBoard[i][k] = maxValue
                if(add_to_max == True):
                    maxValue = maxValue+1
            else:
                paddedBoard[i][k] = board[i-1][k-1]
                paddedSuccessBoard[i][k] = successBoard[i-1][k-1]

    possibleSteps = [[1, 0], [-1, 0], [0, 1], [0, -1]]

    for i in range(1, len(paddedBoard)-1):
        for k in range(1, len(paddedBoard)-1):

            otherTileI, otherTileK = PuzzleFunctions.findTileWithValue(paddedSuccessBoard, paddedBoard[i][k])
            
            for move in possibleSteps:

                if(paddedBoard[i+move[0]][k+move[1]] != paddedSuccessBoard[otherTileI+move[0]][otherTileK+move[1]]):
                    countMisplaced = countMisplaced+1

    misplacedAvg = (float)(countMisplaced)/4.0

    return misplacedAvg