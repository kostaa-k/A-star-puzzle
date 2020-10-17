import PuzzleFunctions
import PuzzleHeuristics
import PuzzleState
from PuzzleState import Node
import bisect
import math
import time
from copy import deepcopy
import DriverFunctions
import pandas as pd


def main():

    successState = PuzzleFunctions.createSuccessState(3)
    possibleVals = PuzzleFunctions.getPossibleValues(3)

    heuristicsDict = PuzzleHeuristics.getHeuristicsDictionary()

    results_df = pd.DataFrame(columns=["Path cost", "Nodes Expanded" ])

    pathCost_df = pd.DataFrame()
    nodesExpanded_df = pd.DataFrame()

    vals = ["h1", "h2", "h3"]


    successDict = PuzzleFunctions.getSuccessDictionary(successState)
    count = 0
    while(count < 15):
        randomState = PuzzleFunctions.createRandomBoard(possibleVals)
        PuzzleFunctions.printBoardNicely(randomState)
        aNode = Node(randomState, None, 0)
        if(aNode.isSolvable()):
            for key in vals:
                nodesExpanded = 0
                finishedNode, nodesExpanded = DriverFunctions.solvePuzzle(aNode, successState, successDict, hVal=key)
                pathCost_df.at[key, "PathCost"+(str)(count)] = finishedNode.pathCost
                nodesExpanded_df.at[key, "NodesExpanded"+str(count)] = nodesExpanded
                print(key, " FINISHED WITH PATH COST: ", finishedNode.pathCost, "NODES EXPANDED: ", nodesExpanded)
            count = count+1
        else:
            print("Not solvable")

    print(pathCost_df)

    print(nodesExpanded_df)



if __name__ == "__main__":
    main()