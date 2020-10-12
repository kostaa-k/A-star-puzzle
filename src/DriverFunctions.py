
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



def depthFirstSearch(aNode, successState, hVal, heuristicDictionary=None):
    if(heuristicDictionary== None):
        heuristicDictionary = PuzzleHeuristics.getHeuristicsDictionary()

    rootNode = deepcopy(aNode)
    frontierNodes = []

    nodesExpanded = 0

    depthCount = 0
    isSolved = False
    while(isSolved == False):

        aNode.getConnectedNodes()

        if(aNode.board == successState):
            isSolved = True

        nodesExpanded = nodesExpanded+1

        for tempNode in aNode.connectedNodes:
            tempNode.heuristic = heuristicDictionary[hVal](tempNode.board, successState)

            #print(tempNode.getTotalScore())
            #time.sleep(3)

            if(tempNode.getTotalScore() <= depthCount):
                bisect.insort(frontierNodes, tempNode)

        if(len(frontierNodes) == 0):
            depthCount = depthCount+1
            print(depthCount)
            aNode = rootNode
            frontierNodes = []
        else:
            aNode = frontierNodes.pop()
            if(aNode.board == successState):
                isSolved = True


    print("Finished")


visitedNodes = {}
newLimit = 1000
def IDA(node, successState, hVal, heuristicDictionary):
    limit = 4
    result = False
    while(result is not True):
        visitedNodes[node.toHash()] = 1
        result = DFS(node, limit, successState, hVal, heuristicDictionary)

        limit = limit+1
        print(limit)
        visitedNodes.clear()

def DFS(node, limit, successState, hVal, heuristicDictionary):


    if(node.board == successState):
        return True
    

    minValue = 10000
    node.getConnectedNodes()
    for tempNode in node.connectedNodes:
        tempNode.heuristic = heuristicDictionary[hVal](tempNode.board, successState)
        if(tempNode.toHash() not in visitedNodes):

            if(tempNode.getTotalScore() <= limit):
                visitedNodes[tempNode.toHash()] = 1
                ans = DFS(tempNode, limit, successState, hVal, heuristicDictionary)

                if(ans == True):
                    return True

            elif (tempNode.getTotalScore() < minValue):
                minValue = tempNode.getTotalScore()
                newLimit = minValue

    return minValue



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