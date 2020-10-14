import PuzzleFunctions


def getHeuristicsDictionary():
    heuristicDictionary = {}
    heuristicDictionary["h1"] = getNumMispacedTiles
    heuristicDictionary["h2"] = getBoardManhattanScore
    heuristicDictionary["h3"] = maxIDMD
    heuristicDictionary["h4"] = getNumberOfIncompleteRowsAndCols
    heuristicDictionary["h5"] = getNumIncorrectRelatives
    heuristicDictionary["h6"] = getNumIncorrectRelatives_add_max_false

    return heuristicDictionary


def getNumMispacedTiles(board, successDictionary):
    #Defined as h2
    displacedCount = 0

    for i in range(0, len(board)):
        for k in range(0, len(board[i])):
            if(board[i][k] != 0):
                zeroTileList = successDictionary[board[i][k]]
                otherTileI = zeroTileList[0]
                otherTileK = zeroTileList[1]
                if(i != otherTileI or k != otherTileK):
                    displacedCount = displacedCount+1

    return displacedCount


def getBoardManhattanScore(board, successDictionary):
    #Defined as h2
    manhattanSum = 0

    for i in range(0, len(board)):
        for k in range(0, len(board[i])):
            if(board[i][k] != 0):
                zeroTileList = successDictionary[board[i][k]]
                otherTileI = zeroTileList[0]
                otherTileK = zeroTileList[1]
                manhattanDiff = abs(otherTileI-i)+abs(otherTileK-k)
                manhattanSum = manhattanSum+manhattanDiff

    return manhattanSum


#THIS CAN BE OUR H3 -> from https://web.archive.org/web/20141224035932/http://juropollo.xe0.ru:80/stp_wd_translation_en.htm
def maxIDMD(board, successDictionary):
    
    return max(getBoardManhattanScore(board, successDictionary), getInversionDistance(board))

def getInversionDistance(board):

    boardRows = PuzzleFunctions.boardTo1DList(board)
    boardCols = PuzzleFunctions.boardTo1DList(PuzzleFunctions.transposeBoard(board))

    verticalInversions = getInversionsInList(boardRows)
    verticalInversions = verticalInversions//3 + (verticalInversions%3)
    horizontalInversions = getInversionsInList(boardCols)
    horizontalInversions = horizontalInversions//3 + (horizontalInversions%3)

    return verticalInversions+horizontalInversions


def getInversionsInList(aList):

    inversionCount = 0

    for i in range (0, len(aList)):
        if(aList[i] != 0):
            for j in range(i+1, len(aList)):
                if (aList[j] < aList[i] and aList[j] != 0):
                    inversionCount = inversionCount+1

    return inversionCount

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

    misplacedAvg = (float)(countMisplaced)/9.0

    return misplacedAvg


def getNumIncorrectRelatives_add_max_false(board, successBoard):
    return getNumIncorrectRelatives(board, successBoard, add_to_max=False)