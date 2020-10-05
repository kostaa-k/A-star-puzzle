

def getDisplacementPairs(board):
    
    displacementPairs = []
    
    for i in range(0, len(board)):
        for k in range(0, len(board[i])):
            currentValue = board[i][k]
            if(currentValue != 0):
                for j in range(i, len(board)):
                    for p in range(k, len(board[j])):
                        if(currentValue > board[j][p]):
                            displacementPairs.append([currentValue, board[j][p]])
                            
    return displacementPairs

def boardToStr(board):
    totalStr = ""
    for i in range(0, len(board)):
        thisList = list(map(str, board[i]))
        tempStr = ".".join(thisList)+"."
        totalStr = totalStr+tempStr
        
    return totalStr[:-1]

def printBoardNicely(board):
    for i in range(0, len(board)):
        for k in range(0, len(board[i])):
            print((str)(board[i][k])+" ", end="")

        print("")