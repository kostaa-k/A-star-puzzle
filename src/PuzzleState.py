import random
from copy import deepcopy
import bisect 
import PuzzleFunctions


class Node:
    board = None
    lastNode = None
    pathCost = None
    heuristic = 0
    possibleMoves = None
    connectedNodes = None

    def __init__(self, board, lastNode, pathCost):
        self.board = board
        self.lastNode = lastNode
        self.pathCost = pathCost
        self.possibleMoves = PuzzleFunctions.getPossibleActions(board)
        self.connectedNodes = []

    def __lt__(self, other):
        return (self.heuristic+self.pathCost) < (other.heuristic+other.pathCost)
        
    def __gt__(self, other):
        return (self.heuristic+self.pathCost) > (other.heuristic+other.pathCost)

    def __str__(self):
        return (str)(self.heuristic+self.pathCost)

    def __eq__(self, other):
        return self.board == other.board and self.pathCost == other.pathCost and self.lastNode == other.lastNode

    def getConnectedNodes(self):
        for aMove in self.possibleMoves:
            theBoard = PuzzleFunctions.makeMove(self.board, aMove)
            if(self.lastNode is not None):
                if(theBoard != self.lastNode.board):
                    self.connectedNodes.append(Node(theBoard, self, self.pathCost+1))
            else:
                self.connectedNodes.append(Node(theBoard, self, self.pathCost+1))

        return self.connectedNodes

    def isSolvable(self):
        return PuzzleFunctions.isBoardSolvable(self.board)

    def setHeuristic(self, value):
        self.heuristic  = value

    def getTotalScore(self):
        return self.pathCost+self.heuristic

    def toHash(self):
        return PuzzleFunctions.boardToStr(self.board)+","+(str)(self.pathCost)