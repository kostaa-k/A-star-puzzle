from copy import deepcopy
import random
import math


def getSuccessDictionary(successBoard):

    returnDict = {}

    for i in range(0, len(successBoard)):
        for k in range(0, len(successBoard[i])):
            returnDict[successBoard[i][k]] = [i, k]

    return returnDict

#8, 16, 24, 35 boards
def getDisplacementPairs(board, empty_tile =0):

    displacementPairs = []
    
    boardStr = boardToStr(board)

    boardList = boardStr.split(".")

    linearBoard = []

    for x in boardList:
        if((int)(x) != empty_tile):
            linearBoard.append((int)(x))


    for i in range(0, len(linearBoard)-1):
        for k in range(i+1, len(linearBoard)):
            if(linearBoard[k] < linearBoard[i]):
                displacementPairs.append([linearBoard[i], linearBoard[k]])
                            
    return displacementPairs

def boardToStr(board):
    totalStr = ""
    for i in range(0, len(board)):
        thisList = list(map(str, board[i]))
        tempStr = ".".join(thisList)+"."
        totalStr = totalStr+tempStr
        
    return totalStr[:-1]

def boardFromStr(boardStr, splitter="."):

    boardArray = boardStr.split(splitter)
    realLen = int(math.sqrt(len(boardArray)))
    newBoard = createEmptyBoard(boardSize=realLen)
    print(boardArray)
    
    count = 0
    for i in range (0, realLen):
        for k in range(0, realLen):
            newBoard[i][k] = (int)(boardArray[count])
            count = count+1
            
    return newBoard

def boardTo1DList(board):

    boardStr = boardToStr(board)

    boardSplit = boardStr.split(".")
    
    outputBoard = []

    for x in boardSplit:
        outputBoard.append(x)

    return outputBoard

def transposeBoard(board):
    
    newBoard = deepcopy(board)

    for i in range(0, len(board)):
        for k in range(0, len(board[i])):
            newBoard[k][i] = board[i][k]

    return newBoard


def createEmptyBoard(boardSize=3):
    theBoard = [[None for i in range(boardSize)] for j in range(boardSize)]

    return theBoard

def printBoardNicely(board):
    for i in range(0, len(board)):
        for k in range(0, len(board[i])):
            print((str)(board[i][k])+" ", end="")

        print("")


def findTileWithValue(board, tileNum):
    
    for i in range(0, len(board)):
        for k in range(0, len(board[i])):
            if(board[i][k] == tileNum):
                return i, k
            
    return None

def getPossibleStates(board, boardHash, emptyTile=0):
    
    zeroList = boardHash[emptyTile]
    emptyI = zeroList[0]
    emptyK = zeroList[1]
     
    possibleSteps = [[1, 0], [-1, 0], [0, 1], [0, -1]]
    
    possibleStates = []
    
    for move in possibleSteps:
        to_i = emptyI+move[0]
        to_k = emptyK+move[1]
        if(to_i >=0 and to_k >= 0 and to_i < len(board) and to_k < len(board[0])):
            board[emptyI][emptyK] = board[to_i][to_k]
            board[to_i][to_k] = emptyTile
            possibleStates.append(deepcopy(board))
            board[to_i][to_k] = board[emptyI][emptyK]
            board[emptyI][emptyK] = emptyTile
    
    return possibleStates


def createRandomBoard(possibleVals):

    boardSize = (int)(math.sqrt(len(possibleVals)))
    
    tempStack = deepcopy(possibleVals)
    board = createEmptyBoard(boardSize=boardSize)
    
    count = 0
    for i in range(0, len(board)):
        for k in range(0, len(board[i])):
            randomNum = random.randint(0, len(tempStack)-1)
            board[i][k] = tempStack[randomNum]
            tempStack.remove(tempStack[randomNum])
            
            count = count+1
            
    return board


def getMaxValue(board):

    maxValue = -1

    for i in range(0, len(board)):
        for k in range(0, len(board[i])):
            if(board[i][k] > maxValue):
                maxValue = board[i][k]

    return maxValue

def isBoardSolvable(board):
    
    return (len(getDisplacementPairs(board)))%2==0


def createSuccessState(boardSize):
    theBoard = createEmptyBoard(boardSize=boardSize)

    count = 0

    for i in range(0, boardSize):
        for k in range(0, boardSize):
            theBoard[i][k] = count
            count = count+1

    return theBoard

def getPossibleValues(kernelSize):
    returnList = []
    for i in range(0, (kernelSize*kernelSize)):
        returnList.append(i)

    return returnList