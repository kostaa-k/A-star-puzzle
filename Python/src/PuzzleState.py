import random
from copy import deepcopy
import bisect 
import PuzzleFunctions
import PuzzleHeuristics


class Node:
    board = None
    lastNode = None
    pathCost = None
    heuristic = 0
    boardHash = None

    def __init__(self, board, lastNode, pathCost):
        self.board = board
        self.lastNode = lastNode
        self.pathCost = pathCost
        self.boardHash = PuzzleFunctions.getSuccessDictionary(board)

    def __lt__(self, other):
        return (self.heuristic+self.pathCost) < (other.heuristic+other.pathCost)
        
    def __gt__(self, other):
        return (self.heuristic+self.pathCost) > (other.heuristic+other.pathCost)

    def __str__(self):
        return (str)(self.heuristic+self.pathCost)

    def __eq__(self, other):
        return self.board == other.board and self.pathCost == other.pathCost and self.lastNode == other.lastNode

    def getConnectedNodes(self):
        connectedNodes = []
        for theBoard in PuzzleFunctions.getPossibleStates(self.board, self.boardHash):
            if(self.lastNode is not None):
                if(theBoard != self.lastNode.board):
                    connectedNodes.append(Node(theBoard, self, self.pathCost+1))
            else:
                connectedNodes.append(Node(theBoard, self, self.pathCost+1))

        return connectedNodes

    def isSolvable(self):
        if(len(self.board)%2 == 1):
            return PuzzleFunctions.isBoardSolvable(self.board)
        else:
            emptyTileI, emptyTileK = PuzzleFunctions.findTileWithValue(self.board, 0)
            rowFromBottom = (len(self.board)-emptyTileI)
            if(rowFromBottom %2 == 0):
                return (len(PuzzleFunctions.getDisplacementPairs(self.board)))%2==1
            else:
                return (len(PuzzleFunctions.getDisplacementPairs(self.board)))%2==0

    def setHeuristic(self, value):
        self.heuristic  = value

    def getTotalScore(self):
        return self.pathCost+self.heuristic

    def toHash(self):
        return PuzzleFunctions.boardToStr(self.board)+","+(str)(self.pathCost)


    def calculateHeuristic(self, hval, successDictionary):
        if(hval == "h1"):
            self.heuristic = PuzzleHeuristics.getNumMispacedTiles(self.board, successDictionary)
        elif(hval == "h2"):
            self.heuristic = PuzzleHeuristics.getBoardManhattanScore(self.board, successDictionary)
        elif(hval == "h3"):
            self.heuristic = PuzzleHeuristics.maxIDMD(self.board, successDictionary)
    