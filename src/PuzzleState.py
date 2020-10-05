import random
from copy import deepcopy
import bisect 
import PuzzleFunctions


class Node:
    board = None
    numDisplacementPairs = None
    lastNode = None
    pathCost = None
    heuristic = None
    possibleMoves = None

    def __init__(self, board, numDisplacementPairs, lastNode, pathCost, heuristic):
        self.board = board
        self.numDisplacementPairs = numDisplacementPairs
        self.lastNode = lastNode
        self.pathCost = pathCost
        self.heuristic = heuristic
        self.possibleMoves = PuzzleFunctions.getPossibleActions(board)

    def __lt__(self, other):
        return self.heuristic < other.heuristic
