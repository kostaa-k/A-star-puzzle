
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

    nodesExpanded = 0
    count = 0
    while(isSolved == False):
        nodesExpanded = nodesExpanded+1
        aNode.getConnectedNodes()

        for tempNode in aNode.connectedNodes:
            tempNode.heuristic = heuristicDictionary[hVal](tempNode.board, successState)

            if(tempNode.toHash() not in statesReached):
                bisect.insort(frontierNodes, tempNode)
                statesReached[tempNode.toHash()] = 1


        aNode = frontierNodes.pop(0)


        if(aNode.board == successState):
            isSolved=True

        count = count+1

    return aNode, nodesExpanded


    print("Finished")


visitedNodes = {}
newLimit = 1000
def IDA(node, successState, successDictionary, hVal="h1"):
    limit = 4
    result = False
    while(result is not True):
        visitedNodes[node.toHash()] = 1
        result = DFS(node, limit, successState, hVal, successDictionary)

        if(result is not None):
            return result, result.pathCost
        limit = limit+1
        #print(limit)
        visitedNodes.clear()

    return

def DFS(node, limit, successState, hVal, successDictionary):


    if(node.board == successState):
        return node
    

    minValue = 10000
    for tempNode in node.getConnectedNodes():
        tempNode.calculateHeuristic(hVal, successDictionary)
        if(tempNode.toHash() not in visitedNodes):

            if(tempNode.getTotalScore() <= limit):
                visitedNodes[tempNode.toHash()] = 1
                ans = DFS(tempNode, limit, successState, hVal, successDictionary)

                if(ans is not None):
                    return ans

            elif (tempNode.getTotalScore() < minValue):
                minValue = tempNode.getTotalScore()
                newLimit = minValue

    return None


# def IDA2(startNode, successState, hVal, heuristicDictionary):

#     threshold = heuristicDictionary[hVal](startNode.board, successState)
#     answer = False
#     while(answer == False):
#         temp = search(startNode, 0, threshold)
#         if(temp is True):
#             return True

#         threshold = temp


# def search(node, g, threshold):



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