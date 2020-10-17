#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <bits/stdc++.h> 
#include<iostream> 
#include <sstream>  // for string streams 
#include <string>
#include <stack>
#include <iterator>
#include <algorithm>

using namespace std;

#define BOARDSIZE 4

typedef struct Node {
    int pathCost;
    char previousMove;
    int board[BOARDSIZE][BOARDSIZE];
    int emptyI;
    int emptyK;
    int countMisplaced;
} node;


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
void idaStar(node);

int search(node, int);
list<node> getNeighbors(node);


//Heuristic Defintions
int getNumMisplacedTiles(int[BOARDSIZE][BOARDSIZE]);
int getManhattanScore(int[BOARDSIZE][BOARDSIZE]);

int getManhattanScoreAdditive(int[BOARDSIZE][BOARDSIZE]);

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

uint64_t countNodes =0;

int main() {
    srand(time(NULL));


    int thisBoard[] = {13,2,10,3,1,12,8,4,5,0,9,6,15,14,11,7};
    int thisBoard2[] = {1,10,15,4,13,6,3,8,2,9,12,7,14,5,0,11};

    //FOR TESTING:
    int thisBoard3[] = {15,3, 8, 2, 14, 9, 13, 11, 0, 5, 6, 12, 4, 10, 1, 7};

    int thisBoard4[] = {3, 0, 11, 5, 15, 14, 6, 13, 8, 2, 9, 10, 7, 1, 4, 12};
    int successBoard[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
    int successBoard3[] = {1,2,3,4,5,6,7,8,0};
    int hardBoard[] = {15,14,8,12,10,11,9,13,2,6,5,1,3,7,4, 0};
    int hardBoard2[] = {0,12,8,4,15,11,7,3,14,10,6,2,13,9,5,1};

    //int additiveSuccessBoard[] = {1,2,3,4,-1,-1, -1, -1, 5}
    int additiveSuccessBoard[] = {1,2,3,4,-1,-1,-1,-1,9,-1,-1,-1,13,-1,-1,-1};

    int possibleValues[(BOARDSIZE*BOARDSIZE)];
    int count =0;

    node startNode2;
    for(int i=0;i<BOARDSIZE;i++){
        for(int k = 0;k<BOARDSIZE;k++){
            //aBoard.board[i][k] = count;
            startNode2.board[i][k] = thisBoard3[count];
            successMapI[successBoard[count]] = i;
            successMapK[successBoard[count]] = k;
            possibleValues[count] = count;
            count = count+1;

            if(k == 0 || i == 0){
                aSuccessMapI[successBoard[count]] = i;
                aSuccessMapK[successBoard[count]] = k;
            }
            else{
                aSuccessMapI[successBoard[count]] = -1;
                aSuccessMapK[successBoard[count]] = -1;
            }

        }
    }

    int solvedCount = 0;
    int unsolvedCount = 0;
    while(solvedCount < 1){

        //node randomNode = createRandomBoard(possibleValues);

        //node startNode = createRandomBoard(possibleValues);
        node startNode = startNode2;
        startNode.emptyI = findIValue(startNode.board, 0);
        startNode.emptyK = findKValue(startNode.board, 0);
        startNode.pathCost = 0;
        startNode.previousMove='N';
        startNode.countMisplaced = getNumMisplacedTiles(startNode.board);

        if( isSolvable(startNode.board) == true){
            //cout << "SOLVABLE:\n";

            printBoard(startNode.board);
            
            fflush(stdout);
            idaStar(startNode);
            cout << getManhattanScoreAdditive(startNode.board);
            solvedCount = solvedCount+1;
            cout << "\n";
        }
        else{
            unsolvedCount = unsolvedCount+1;
        }

        fflush(stdout);
        


    }

    //string hashValue = getBoardHash(rNeighbor.currentBoard.board)
    //idaStar(startNode);

    //getBoardHash(rNeighbor);


    return 0;
}



void idaStar(node tempNode){

    int depth=0;
    visitedNodes.clear();

    

    int result = 100;

    fflush(stdout);
    while(result >= 0 && depth < 70){
        depth = depth+1;
        //unordered_set <uint64_t> visitedStates;
        //visitedStates.insert(getBoardHash(tempNode.board, tempNode.pathCost));
        result = search(tempNode, depth);

        // cout << "Searched depth: ";
        // cout << depth; 
        // cout << "\n";
        // fflush(stdout);

        if(depth%5 == 0 && depth> 30){
            cout << "Searched depth: ";
            cout << depth; 
            cout << "\n";
            fflush(stdout);
        }

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

    countNodes = 0;
}

int DFS(node theNode, int limit){

    countNodes++;

    if(theNode.pathCost+getManhattanScore(theNode.board)> limit){
        return theNode.pathCost;
    }
    if(isBoardSolved(theNode.board)){
        return -theNode.pathCost;
    }

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

int search(node theNode, int limit){



    if(theNode.pathCost+getManhattanScore(theNode.board) > limit){
        return theNode.pathCost;
    }

    countNodes++;

    if (getManhattanScoreAdditive(theNode.board) == 0){
        return -theNode.pathCost;
    }


    if(isBoardSolved(theNode.board)){
        return -theNode.pathCost;
    }

    list<node> neighbors = getNeighbors(theNode);

    for (std::list<node>::iterator currentNeighbor = neighbors.begin(); currentNeighbor != neighbors.end(); ++currentNeighbor){
        
        node theNeighbor = *currentNeighbor;

        int answer = search(theNeighbor, limit);
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
    //int toSwitch = aNode.currentBoard.board[aNode.currentBoard.emptyI][aNode.currentBoard.emptyK+1];
    //int oldEmptyI =  aNode.currentBoard.emptyI;
    //int oldEmptyK = aNode.currentBoard.emptyK;
    aNode.emptyK++;
    aNode.pathCost++;
    aNode.previousMove = 'R';

    // node returnNode;
    // returnNode.currentBoard = aNode.currentBoard;

    // returnNode.currentBoard.emptyI = aNode.currentBoard.emptyI;
    // returnNode.currentBoard.emptyK = oldEmptyK+1;
    // returnNode.currentBoard.board[oldEmptyI][oldEmptyK] = aNode.currentBoard.board[aNode.currentBoard.emptyI][aNode.currentBoard.emptyK+1];
    // returnNode.currentBoard.board[oldEmptyI][oldEmptyK+1] = 0;
    // returnNode.pathCost = aNode.pathCost+1;
    // returnNode.previousMove = 'R';

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
    //int toSwitch = aNode.currentBoard.board[aNode.currentBoard.emptyI][aNode.currentBoard.emptyK+1];
    //int oldEmptyI =  aNode.currentBoard.emptyI;
    //int oldEmptyK = aNode.currentBoard.emptyK;
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
    
    //int toSwitch = aNode.currentBoard.board[aNode.currentBoard.emptyI][aNode.currentBoard.emptyK+1];
    //int oldEmptyI =  aNode.currentBoard.emptyI;
    //int oldEmptyK = aNode.currentBoard.emptyK;
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

    //int toSwitch = aNode.currentBoard.board[aNode.currentBoard.emptyI][aNode.currentBoard.emptyK+1];
    //int oldEmptyI =  aNode.currentBoard.emptyI;
    //int oldEmptyK = aNode.currentBoard.emptyK;
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


            //cout << theList[count];
            //cout << "\n";
            newboard.board[i][k] = theList[count];

            count = count+1;
        }
    }

    newboard.emptyI = findIValue(newboard.board, 0);
    newboard.emptyK = findKValue(newboard.board, 0);

    return newboard;
}

