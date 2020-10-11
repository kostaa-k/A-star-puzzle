
import PuzzleFunctions
import PuzzleHeuristics
from PuzzleState import Node
import bisect
import math
import time
from copy import deepcopy


def solvePuzzle(aNode, successState, hVal, heuristicDictionary=None):
    if(heuristicDictionary== None):
        heuristicDictionary = PuzzleHeuristics.getHeuristicsDictionary()

    statesReached = {}

    isSolved = False

    frontierNodes = []

    print(len(frontierNodes))

    nodesExpanded = 0
    while(isSolved == False):

        nodesExpanded = nodesExpanded+1
        aNode.getConnectedNodes()

        for tempNode in aNode.connectedNodes:
            tempNode.heuristic = heuristicDictionary[hVal](tempNode.board, successState)

            if(PuzzleFunctions.boardToStr(tempNode.board) not in statesReached):
                bisect.insort(frontierNodes, tempNode)
                statesReached[PuzzleFunctions.boardToStr(tempNode.board)] = tempNode

            elif(statesReached[PuzzleFunctions.boardToStr(tempNode.board)].pathCost > tempNode.pathCost):
                
                theIndex = binarySearch(frontierNodes, statesReached[PuzzleFunctions.boardToStr(tempNode.board)])

                if (theIndex != -1):
                    del frontierNodes[theIndex]

                bisect.insort(frontierNodes, tempNode)

                statesReached[PuzzleFunctions.boardToStr(tempNode.board)] = tempNode


        aNode = frontierNodes.pop(0)


        if(aNode.board == successState):
            isSolved=True

        
    print("FINISHED")
    print("Steps: ", aNode.pathCost)

    return aNode, nodesExpanded


def binarySearch(alist, item):
    first = 0
    last = len(alist)-1
    found = False

    while (first<=last and not found):
        midpoint = (first + last)//2
        if (alist[midpoint] == item):
            return midpoint
        else:
            if (item < alist[midpoint]):
                last = midpoint-1
            else:
                first = midpoint+1

    return False