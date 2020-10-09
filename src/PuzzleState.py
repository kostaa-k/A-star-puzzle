import random
from copy import deepcopy
import bisect 
import PuzzleFunctions


class Node:
    board = None
    lastNode = None
    pathCost = None
    heuristic = None
    possibleMoves = None
    connectedNodes = []

    def __init__(self, board, lastNode, pathCost, heuristic):
        self.board = board
        self.lastNode = lastNode
        self.pathCost = pathCost
        self.heuristic = heuristic
        self.possibleMoves = PuzzleFunctions.getPossibleActions(board)

    def __lt__(self, other):
        return self.heuristic < other.heuristic

    def getConnectedNodes(self):
        for aMove in self.possibleMoves:
            theBoard = PuzzleFunctions.makeMove(self.board, aMove)
            if(theBoard != self.lastNode.board):
                self.connectedNodes.append(Node(theBoard, self, self.pathCost+1, self.heuristic+1))

