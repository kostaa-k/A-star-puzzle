from copy import deepcopy
import random
import math

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

def getPossibleActions(board, emptyTile=0):
    
    emptyI, emptyK = findTileWithValue(board, emptyTile)
     
    possibleSteps = [[1, 0], [-1, 0], [0, 1], [0, -1]]
    
    possibleMoves = []
    
    for move in possibleSteps:
        tempMove = {}
        to_i = emptyI+move[0]
        to_k = emptyK+move[1]
        if(to_i >=0 and to_k >= 0 and to_i < len(board) and to_k < len(board[0])):
            tempMove["from"] = [emptyI, emptyK]
            tempMove["to"] = [to_i, to_k]
            possibleMoves.append(tempMove)
    
    return possibleMoves


def getPossibleStates(board, possibleMoves):
    
    possibleStates = []
    
    for move in possibleMoves:
        new_board = makeMove(board, move)
        
        possibleStates.append((new_board))
        
    return possibleStates


def makeMove(board, move):
    
    newBoard = deepcopy(board)
    
    fromCoords = move["from"]
    toCoords = move["to"]
    
    newBoard[fromCoords[0]][fromCoords[1]] = board[toCoords[0]][toCoords[1]]
    newBoard[toCoords[0]][toCoords[1]] = board[fromCoords[0]][fromCoords[1]]
    
    return newBoard

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