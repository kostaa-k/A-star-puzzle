#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <bits/stdc++.h> 
#include <iostream> 
#include <sstream>  // for string streams 
#include <string>
#include <stack>
#include <iterator>
#include <algorithm>
#include <fstream>

using namespace std;


//CHANGE THIS VALUE BETWEEN 3 and 5 for different board configurations
#define BOARDSIZE 4


int heuristicVal = 3;

int minValue;

typedef struct Node {
    int pathCost;
    char previousMove;
    int board[BOARDSIZE][BOARDSIZE];
    int emptyI;
    int emptyK;
    int countMisplaced;
} node;

typedef struct resultStruct {
    node startNode;
    uint64_t nodesExpanded;
    int pathCost;
} resultstruct;


void printBoard(int aboard[BOARDSIZE][BOARDSIZE]);


//Success Map definitions
int successMapI[BOARDSIZE*BOARDSIZE];
int successMapK[BOARDSIZE*BOARDSIZE];
int aSuccessMapI[BOARDSIZE*BOARDSIZE];
int aSuccessMapK[BOARDSIZE*BOARDSIZE];

//Visited Nodes definition
unordered_set <uint64_t> visitedNodes;

//A* Algorithm Definitions
int DFS(node, int);
resultstruct idaStar(node);

list<node> getNeighbors(node);


//Heuristic Defintions
int getNumMisplacedTiles(int[BOARDSIZE][BOARDSIZE]);
int getManhattanScore(int[BOARDSIZE][BOARDSIZE]);

int getManhattanScoreAdditive(int[BOARDSIZE][BOARDSIZE]);

int getInversionsInList(int [BOARDSIZE]);

int getLinearConflicts(int[BOARDSIZE][BOARDSIZE]);

//GamePlay Functions
node getNeighborR(node);
node getNeighborL(node);
node getNeighborU(node);
node getNeighborD(node);

bool isBoardSolved(int[BOARDSIZE][BOARDSIZE]);
uint64_t getBoardHash(int[BOARDSIZE][BOARDSIZE], int);
int findKValue(int[BOARDSIZE][BOARDSIZE], int);
int findIValue(int[BOARDSIZE][BOARDSIZE], int);
int getInversionNum(int[BOARDSIZE][BOARDSIZE]);
bool isSolvable(int[BOARDSIZE][BOARDSIZE]);
node createRandomBoard(int[BOARDSIZE*BOARDSIZE]);

node randomBoardWithinMoves(node, int);

//Output Functions
void writeResultsToCSV(string, resultstruct[100], resultstruct[100], resultstruct[100], int);

uint64_t countNodes = 0;

int main() {
    srand(time(NULL));


    int thisBoard[] = {13,2,10,3,1,12,8,4,5,0,9,6,15,14,11,7};
    int thisBoard2[] = {1,10,15,4,13,6,3,8,2,9,12,7,14,5,0,11};

    //FOR TESTING:
    int thisBoard3[] = {15,3, 8, 2, 14, 9, 13, 11, 0, 5, 6, 12, 4, 10, 1, 7};

    int thisBoard4[] = {3, 0, 11, 5, 15, 14, 6, 13, 8, 2, 9, 10, 7, 1, 4, 12};
    int successBoard4[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
    int successBoard3[] = {1,2,3,4,5,6,7,8,0};

    int successBoard5[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0};

    int hardBoard[] = {15,14,8,12,10,11,9,13,2,6,5,1,3,7,4, 0};
    int hardBoard2[] = {0,12,8,4,15,11,7,3,14,10,6,2,13,9,5,1};

    //int additiveSuccessBoard[] = {1,2,3,4,-1,-1, -1, -1, 5}
    int additiveSuccessBoard[] = {1,2,3,4,-1,-1,-1,-1,9,-1,-1,-1,13,-1,-1,-1};

    int possibleValues[(BOARDSIZE*BOARDSIZE)];
    int count =0;

    node startNode2;
    node successNode;
    for(int i=0;i<BOARDSIZE;i++){
        for(int k = 0;k<BOARDSIZE;k++){

            if(BOARDSIZE == 3){
                successMapI[successBoard3[count]] = i;
                successMapK[successBoard3[count]] = k;
                possibleValues[count] = count;

                successNode.board[i][k] = successBoard3[count];

                count = count+1;

                if(k == 0 || i == 0){
                    aSuccessMapI[successBoard3[count]] = i;
                    aSuccessMapK[successBoard3[count]] = k;
                }
                else{
                    aSuccessMapI[successBoard3[count]] = -1;
                    aSuccessMapK[successBoard3[count]] = -1;
                }
            }
            else if (BOARDSIZE == 4){
                successMapI[successBoard4[count]] = i;
                successMapK[successBoard4[count]] = k;
                possibleValues[count] = count;

                successNode.board[i][k] = successBoard4[count];

                count = count+1;

                if(k == 0 || i == 0){
                    aSuccessMapI[successBoard4[count]] = i;
                    aSuccessMapK[successBoard4[count]] = k;
                }
                else{
                    aSuccessMapI[successBoard4[count]] = -1;
                    aSuccessMapK[successBoard4[count]] = -1;
                }
            }
            else if (BOARDSIZE == 5){
                successMapI[successBoard5[count]] = i;
                successMapK[successBoard5[count]] = k;
                possibleValues[count] = count;

                successNode.board[i][k] = successBoard5[count];

                count = count+1;

                if(k == 0 || i == 0){
                    aSuccessMapI[successBoard5[count]] = i;
                    aSuccessMapK[successBoard5[count]] = k;
                }
                else{
                    aSuccessMapI[successBoard5[count]] = -1;
                    aSuccessMapK[successBoard5[count]] = -1;
                }

            }

        }
    }



    successNode.pathCost = 0;
    successNode.emptyI = successMapI[0];
    successNode.emptyK = successMapK[0];
    successNode.previousMove = 'N';

    int solvedCount = 0;
    int unsolvedCount = 0;

    resultstruct resultsH1[100];
    resultstruct resultsH2[100];
    resultstruct resultsH3[100];

    int runToSolutions = 100;

    while(solvedCount < runToSolutions){

        //node startNode = createRandomBoard(possibleValues);
        node startNode = randomBoardWithinMoves(successNode, 38);
        startNode.emptyI = findIValue(startNode.board, 0);
        startNode.emptyK = findKValue(startNode.board, 0);
        startNode.pathCost = 0;
        startNode.previousMove='N';
        startNode.countMisplaced = getNumMisplacedTiles(startNode.board);

        if( isSolvable(startNode.board) == true){
            for (int i=1;i<4;i++){
                heuristicVal = i;
                printBoard(startNode.board);
                fflush(stdout);
                resultstruct resultStats = idaStar(startNode);
                if(i == 1){
                    resultsH1[solvedCount] = resultStats;
                }
                else if (i == 2){
                    resultsH2[solvedCount] = resultStats;
                }
                else if (i == 3){
                    resultsH3[solvedCount] = resultStats;
                }

                cout << "\n";

            }
            solvedCount = solvedCount+1;
        }
        else{
            unsolvedCount = unsolvedCount+1;
        }

        fflush(stdout);
        

    }

    writeResultsToCSV("resultsLessThan40Moves.csv", resultsH1, resultsH2, resultsH3, runToSolutions);


    return 0;
}



resultstruct idaStar(node tempNode){

    int depth=0;

    resultstruct resultObject;
    resultObject.startNode = tempNode;

    

    int result = 100;

    fflush(stdout);
    countNodes = 0;
    while(result >= 0 && depth < 70){
        minValue = 10000;
        result = DFS(tempNode, depth);

        cout << depth;
        cout << "\n";
        depth = minValue;

        visitedNodes.clear();

        
    }

    if(result < 0){
        cout << "FOUND RESULT in steps: ";
        cout << result*-1;
        cout << "\n";
    }
    
    cout << "Count of Nodes searched:";
    cout << countNodes;
    cout << "\n";

    resultObject.nodesExpanded = countNodes;
    resultObject.pathCost = result*-1;

    return resultObject;
}

int DFS(node theNode, int limit){

    int totalCost;

    switch(heuristicVal){
        case 1:
            totalCost = theNode.pathCost+theNode.countMisplaced;
            break;
        case 2:
            totalCost = theNode.pathCost+getManhattanScore(theNode.board);
            break;
        case 3:
            totalCost = theNode.pathCost+getLinearConflicts(theNode.board);
            break;
    }
    if(totalCost > limit){
        if (totalCost < minValue){
            minValue = totalCost;
        }
        return theNode.pathCost;
    }
    if(isBoardSolved(theNode.board)){
        return -theNode.pathCost;
    }

    countNodes++;

    if(theNode.previousMove != 'R' && theNode.emptyK > 0){
        //node neighbor = getNeighborL(theNode);
        int answer = DFS(getNeighborL(theNode), limit);
        if(answer < 0){
            return answer;
        }

    }
    if(theNode.previousMove != 'L' && theNode.emptyK < (BOARDSIZE-1)){
        int answer = DFS(getNeighborR(theNode), limit);
        if(answer < 0){
            return answer;
        }
        
    }
    if(theNode.previousMove != 'D' && theNode.emptyI > 0){
        int answer = DFS(getNeighborU(theNode), limit);
        if(answer < 0){
            return answer;
        }

    }
    if(theNode.previousMove != 'U' && theNode.emptyI < (BOARDSIZE-1)){
        //node dNode = getNeighborD(theNode);
        int answer = DFS(getNeighborD(theNode), limit);
        if(answer < 0){
            return answer;
        }
    }

    return limit;
}


list<node> getNeighbors(node theNode){

    list<node> returnNodes;
    if(theNode.previousMove != 'R' && theNode.emptyK > 0){
        returnNodes.push_back(getNeighborL(theNode));
    }
    if(theNode.previousMove != 'L' && theNode.emptyK < (BOARDSIZE-1)){
        returnNodes.push_back(getNeighborR(theNode));
    }
    if(theNode.previousMove != 'D' && theNode.emptyI > 0){
        returnNodes.push_back(getNeighborU(theNode));

    }
    if(theNode.previousMove != 'U' && theNode.emptyI < (BOARDSIZE-1)){
        returnNodes.push_back(getNeighborD(theNode));
    }

    return returnNodes;
}


node getNeighborR(node aNode){
    int toSwitch = aNode.board[aNode.emptyI][aNode.emptyK+1];
    aNode.board[aNode.emptyI][aNode.emptyK] = toSwitch;
    aNode.board[aNode.emptyI][aNode.emptyK+1] = 0;
    if(aNode.emptyI == successMapI[toSwitch]){
        if(aNode.emptyK == successMapK[toSwitch]){
            aNode.countMisplaced--;
        }
        else if(aNode.emptyK+1 == successMapK[toSwitch]){
            aNode.countMisplaced++;
        }
    }
    aNode.emptyK++;
    aNode.pathCost++;
    aNode.previousMove = 'R';


    return aNode;
}


node getNeighborL(node aNode){
    int toSwitch = aNode.board[aNode.emptyI][aNode.emptyK-1];

    aNode.board[aNode.emptyI][aNode.emptyK] = toSwitch;
    aNode.board[aNode.emptyI][aNode.emptyK-1] = 0;

    if(aNode.emptyI == successMapI[toSwitch]){
        if(aNode.emptyK == successMapK[toSwitch]){
            aNode.countMisplaced--;
        }
        else if(aNode.emptyK-1 == successMapK[toSwitch]){
            aNode.countMisplaced++;
        }
    }
    aNode.emptyK--;
    aNode.pathCost++;
    aNode.previousMove = 'L';

    return aNode;
}

node getNeighborU(node aNode){

    int toSwitch = aNode.board[aNode.emptyI-1][aNode.emptyK];
    aNode.board[aNode.emptyI][aNode.emptyK] = toSwitch;
    aNode.board[aNode.emptyI-1][aNode.emptyK] = 0;

    if(aNode.emptyK == successMapK[toSwitch]){
        if(aNode.emptyI == successMapI[toSwitch]){
            aNode.countMisplaced--;
        }
        else if(aNode.emptyI-1 == successMapI[toSwitch]){
            aNode.countMisplaced++;
        }
    }
    
    aNode.emptyI--;
    aNode.pathCost++;
    aNode.previousMove = 'U';

    return aNode;

}


node getNeighborD(node aNode){
    int toSwitch = aNode.board[aNode.emptyI+1][aNode.emptyK];
    aNode.board[aNode.emptyI][aNode.emptyK] = toSwitch;
    aNode.board[aNode.emptyI+1][aNode.emptyK] = 0;

    if(aNode.emptyK == successMapK[toSwitch]){
        if(aNode.emptyI == successMapI[toSwitch]){
            aNode.countMisplaced--;
        }
        else if(aNode.emptyI+1 == successMapI[toSwitch]){
            aNode.countMisplaced++;
        }
    }

    aNode.emptyI++;
    aNode.pathCost++;
    aNode.previousMove = 'D';

    return aNode;
    
}


int getManhattanScoreAdditive(int aboard[BOARDSIZE][BOARDSIZE]){
    int manhattanSum = 0;

    for(int i =0;i<BOARDSIZE;i++){
        for(int k=0;k<BOARDSIZE;k++){
            int currentValue = aboard[i][k];
            if(currentValue != 0 and aSuccessMapI[currentValue] != -1){
                manhattanSum+= abs(successMapI[currentValue]-i) +abs(successMapK[currentValue] -k);
            }
        }
    }

    return manhattanSum;
}

int getLinearConflicts(int aboard[BOARDSIZE][BOARDSIZE]){

    int inversionCount = 0;
    int successCol[BOARDSIZE][BOARDSIZE];
    int successRow[BOARDSIZE][BOARDSIZE];

    for(int i =0;i<BOARDSIZE;i++){
        for(int k=0;k<BOARDSIZE;k++){
            int currentValueRow = aboard[i][k];
            int currentValueCol = aboard[k][i];

            successCol[i][k] = -1;
            successRow[i][k] = -1;
            
            if(currentValueRow != 0){
                if(i == successMapI[currentValueRow]){
                    successRow[i][k] = currentValueRow;
                }
            }

            if(currentValueCol != 0){
                if(i == successMapK[currentValueCol]){
                    successCol[i][k] = currentValueCol;
                }
            }
        }
    }

    //printBoard(successCol);
    //printBoard(successRow);

    for(int i =0;i<BOARDSIZE;i++){
        inversionCount = inversionCount+getInversionsInList(successCol[i])+getInversionsInList(successRow[i]);
    }

    return 2*inversionCount+getManhattanScore(aboard);
}

int getInversionsInList(int aList[BOARDSIZE]){
    
    int inversionCount = 0;

    for(int i =0;i<BOARDSIZE;i++){
        if(aList[i] > 0){
            for(int j=i+1;j<BOARDSIZE;j++){
                if(aList[j] < aList[i] && aList[j] > 0){
                    inversionCount++;
                }
            }

        }

    }

    return inversionCount;
}


int getManhattanScore(int aboard[BOARDSIZE][BOARDSIZE]){
    int manhattanSum = 0;

    for(int i =0;i<BOARDSIZE;i++){
        for(int k=0;k<BOARDSIZE;k++){
            int currentValue = aboard[i][k];
            if(currentValue != 0){
                manhattanSum+= abs(successMapI[currentValue]-i) +abs(successMapK[currentValue] -k);
            }
        }
    }

    return manhattanSum;
}

int getNumMisplacedTiles(int aboard[BOARDSIZE][BOARDSIZE]){
    int numMisplaced = 0;

    for(int i =0;i<BOARDSIZE;i++){
        for(int k=0;k<BOARDSIZE;k++){
            int currentValue = aboard[i][k];
            if(currentValue != 0){
                if(i != successMapI[currentValue] || k != successMapK[currentValue]){
                    numMisplaced++;
                }
            }
        }
    }

    return numMisplaced;

}


void printBoard(int aboard[BOARDSIZE][BOARDSIZE]){
    printf("\n");
    for(int i =0;i<BOARDSIZE;i++){
        for(int k=0;k<BOARDSIZE;k++){
            printf("%d ", aboard[i][k]);
        }
        printf("\n");
    }
}


uint64_t getBoardHash(int aboard[BOARDSIZE][BOARDSIZE], int pathCost){
    
    uint64_t totalNum = 0;

    for (int i=0; i<BOARDSIZE;i++){
        for (int j=0;j<BOARDSIZE;j++){
            totalNum = totalNum << 4;
            totalNum = totalNum+aboard[i][j];
        }
    }

    //totalNum = totalNum << 4;
    //totalNum = totalNum+pathCost;

    return totalNum;
}


bool isBoardSolved(int aboard[BOARDSIZE][BOARDSIZE]){

    for (int i=0; i<BOARDSIZE;i++){
        for (int k=0;k<BOARDSIZE;k++){
            if(i != successMapI[aboard[i][k]] || k != successMapK[aboard[i][k]]){
                return false;
            }
        }
    }

    return true;

}

int findIValue(int aboard[BOARDSIZE][BOARDSIZE], int theValue){

    for (int i=0; i<BOARDSIZE;i++){
        for (int k=0;k<BOARDSIZE;k++){
            if(aboard[i][k] == theValue){
                return i;
            }
        }
    }

    return -1;
}

int findKValue(int aboard[BOARDSIZE][BOARDSIZE], int theValue){

    for (int i=0; i<BOARDSIZE;i++){
        for (int k=0;k<BOARDSIZE;k++){
            if(aboard[i][k] == theValue){
                return k;
            }
        }
    }

    return -1;
}

bool isSolvable(int aboard[BOARDSIZE][BOARDSIZE]){
    if(BOARDSIZE%2 == 0){
        int iVal = findIValue(aboard, 0);
        int kVal = findKValue(aboard, 0);
        int rowFromBottom = BOARDSIZE-iVal;
        //cout << "Row from bottom: ";
        //cout << rowFromBottom;
        //cout << "\n";
        if(rowFromBottom%2 == 0){
            return getInversionNum(aboard)%2==1;
        }
        else{
            return getInversionNum(aboard)%2==0;
        }
    }
    else{
        return getInversionNum(aboard)%2==0;
    }
}

int getInversionNum(int aboard[BOARDSIZE][BOARDSIZE]){

    int linearList[(BOARDSIZE*BOARDSIZE)-1];
    int count = 0 ;
    for (int i=0; i<BOARDSIZE;i++){
        for (int k=0;k<BOARDSIZE;k++){
            if(aboard[i][k] != 0){
                linearList[count] = aboard[i][k];
                count = count+1;
            }
        }
    }

    int numInversions = 0;

    for(int i=0;i<((BOARDSIZE*BOARDSIZE)-2);i++){
        //cout << linearList[i];
        //cout << " ";
        for(int j=i+1;j<((BOARDSIZE*BOARDSIZE)-1);j++){
            if(linearList[j] < linearList[i]){
                numInversions = numInversions+1;
            }
        }
    }
    //cout << "\n Number of inversions: ";
    //cout << numInversions;
    //cout << "\n";

    return numInversions;
}


node createRandomBoard(int possibleValues[BOARDSIZE*BOARDSIZE]){

    int maxVal = BOARDSIZE*BOARDSIZE;

    vector<int> theList;

    for(int i=0;i<(BOARDSIZE*BOARDSIZE);i++){
        theList.push_back(possibleValues[i]);
    }

    node newboard;

    std::random_shuffle ( theList.begin(), theList.end() );

    int count = 0;
    for(int i=0;i<BOARDSIZE;i++){
        for(int k=0;k<BOARDSIZE;k++){

            newboard.board[i][k] = theList[count];

            count = count+1;
        }
    }

    newboard.emptyI = findIValue(newboard.board, 0);
    newboard.emptyK = findKValue(newboard.board, 0);

    return newboard;
}

node randomBoardWithinMoves(node successState, int moveThreshold){

    unordered_set <uint64_t> visitedStates;

    int maxVal = BOARDSIZE*BOARDSIZE;

    int counter = 0;

    int randomMove = -1;

    while(counter < moveThreshold){

        list<node> theNeighbors = getNeighbors(successState);

        randomMove =  std::rand() % (theNeighbors.size());

        bool foundMove = false;

        while(foundMove == false){
            auto l_front = theNeighbors.begin();
            std::advance(l_front, randomMove);
            node toLookFor = *l_front;
            if(visitedStates.find(getBoardHash(toLookFor.board, 0)) == visitedStates.end()){
                foundMove = true;
                successState = toLookFor;
            }
            randomMove =  std::rand() % (theNeighbors.size());
        }

        counter++;
    }

    return successState;
}


void writeResultsToCSV(string fileName, resultstruct resultStats1[100], resultstruct resultStats2[100], resultstruct resultStats3[100], int numberOFRuns){

    ofstream outputFile;
    outputFile.open(fileName);

    outputFile << "Puzzle #";

    outputFile << ",h1 # of Steps";
    outputFile << ",h1 # Nodes Expanded";

    outputFile << ",h2 # of Steps";
    outputFile << ",h2 # Nodes Expanded";

    outputFile << ",h3 # of Steps";
    outputFile << ",h3 # Nodes Expanded";

    outputFile << "\n";

    for(int i=0;i<numberOFRuns;i++){

        outputFile << i+1;
        //Print h1
        if(resultStats1[i].pathCost != 0){
            outputFile << ","+to_string(resultStats1[i].pathCost);
            outputFile << ","+to_string(resultStats1[i].nodesExpanded);
        }

        //Print h2
        if(resultStats2[i].pathCost != 0){
            outputFile << ","+to_string(resultStats2[i].pathCost);
            outputFile << ","+to_string(resultStats2[i].nodesExpanded);
        }

        //Print h3
        if(resultStats3[i].pathCost != 0){
            outputFile << ","+to_string(resultStats3[i].pathCost);
            outputFile << ","+to_string(resultStats3[i].nodesExpanded);
        }

        outputFile << "\n";
    }
    outputFile.close();
}