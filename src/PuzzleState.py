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
        return (self.heuristic+self.pathCost) < (other.heuristic+self.pathCost)

    def getConnectedNodes(self):
        for aMove in self.possibleMoves:
            theBoard = PuzzleFunctions.makeMove(self.board, aMove)
            if(self.lastNode is not None):
                if(theBoard != self.lastNode.board):
                    self.connectedNodes.append(Node(theBoard, self, self.pathCost+1))
            else:
                self.connectedNodes.append(Node(theBoard, self, self.pathCost+1))

    def isSolvable(self):
        return PuzzleFunctions.isBoardSolvable(self.board)

    def setHeuristic(self, value):
        self.heuristic  = value

    def getTotalScore(self):
        return self.pathCost+self.heuristic