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

typedef struct Board {
    int board[BOARDSIZE][BOARDSIZE];
    int emptyI;
    int emptyK;
} board;


typedef struct Node {
    int pathCost;
    board currentBoard;
    char previousMove;
} node;


typedef struct SuccessBoard {
    int board[BOARDSIZE][BOARDSIZE];
    int emptyI;
    int emptyK;
    int iMap[BOARDSIZE*BOARDSIZE];
    int kMap[BOARDSIZE*BOARDSIZE];
} successboard;


void printBoard(int aboard[BOARDSIZE][BOARDSIZE]);

board *aBoard;
successboard *successState;

//Success Map definitions
int successMapI[BOARDSIZE*BOARDSIZE];
int successMapK[BOARDSIZE*BOARDSIZE];

//Visited Nodes definition
unordered_set <uint64_t> visitedNodes;

//A* Algorithm Definitions
int DFS(node, int);
void idaStar(node);

//Heuristic Defintions
int getNumMisplacedTiles(int[BOARDSIZE][BOARDSIZE]);
int getManhattanScore(int[BOARDSIZE][BOARDSIZE]);

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
board createRandomBoard(int[BOARDSIZE*BOARDSIZE]);

uint64_t countNodes =0;

int main() {
    srand(time(NULL));

   board aBoard;
   successState = (successboard*) malloc(sizeof(successboard));

    int thisBoard[] = {13,2,10,3,1,12,8,4,5,0,9,6,15,14,11,7};
    int thisBoard2[] = {1,10,15,4,13,6,3,8,2,9,12,7,14,5,0,11};
    int thisBoard3[] = {15,3, 8, 2, 14, 9, 13, 11, 0, 5, 6, 12, 4, 10, 1, 7};
    int thisBoard4[] = {3, 0, 11, 5, 15, 14, 6, 13, 8, 2, 9, 10, 7, 1, 4, 12};
    int successBoard[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
    int successBoard3[] = {1,2,3,4,5,6,7,8,0};
    int hardBoard[] = {15,14,8,12,10,11,9,13,2,6,5,1,3,7,4, 0};

    int possibleValues[(BOARDSIZE*BOARDSIZE)];
    int count =0;
    for(int i=0;i<BOARDSIZE;i++){
        for(int k = 0;k<BOARDSIZE;k++){
            //aBoard.board[i][k] = count;
            aBoard.board[i][k] = thisBoard3[count];
            successMapI[successBoard[count]] = i;
            successMapK[successBoard[count]] = k;
            possibleValues[count] = count;
            count = count+1;

        }
    }

    int solvedCount = 0;
    int unsolvedCount = 0;
    while(solvedCount < 1){

        //board newBoard = createRandomBoard(possibleValues);

        node startNode;
        startNode.currentBoard= aBoard;
        startNode.currentBoard.emptyI = findIValue(startNode.currentBoard.board, 0);
        startNode.currentBoard.emptyK = findKValue(startNode.currentBoard.board, 0);
        startNode.pathCost = 0;
        startNode.previousMove='N';

        if( isSolvable(startNode.currentBoard.board) == true){
            //cout << "SOLVABLE:\n";

            printBoard(startNode.currentBoard.board);
            
            fflush(stdout);
            idaStar(startNode);
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
        result = DFS(tempNode, depth);

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

    countNodes = countNodes+1;
    
    // uint64_t value = getBoardHash(theNode.currentBoard.board, theNode.pathCost);
    // if(visitedNodes.find(value) == visitedNodes.end()){
    //     visitedNodes.insert(value);
    //     countNodes = countNodes+1;
    // }
    // else{
    //     return 1;
    // }


    if(theNode.pathCost+getManhattanScore(theNode.currentBoard.board) > limit){
        return theNode.pathCost;
    }
    if(isBoardSolved(theNode.currentBoard.board)){
        return -theNode.pathCost;
    }

    if(theNode.previousMove != 'R' && theNode.currentBoard.emptyK > 0){
        int answer = DFS(getNeighborL(theNode), limit);
        if(answer < 0){
            return answer;
        }

    }
    if(theNode.previousMove != 'L' && theNode.currentBoard.emptyK < (BOARDSIZE-1)){
        int answer = DFS(getNeighborR(theNode), limit);
        if(answer < 0){
            return answer;
        }
        
    }
    if(theNode.previousMove != 'D' && theNode.currentBoard.emptyI > 0){
        int answer = DFS(getNeighborU(theNode), limit);
        if(answer < 0){
            return answer;
        }

    }
    if(theNode.previousMove != 'U' && theNode.currentBoard.emptyI < (BOARDSIZE-1)){
        //node dNode = getNeighborD(theNode);
        int answer = DFS(getNeighborD(theNode), limit);
        if(answer < 0){
            return answer;
        }
    }

    return limit;
}


node getNeighborR(node aNode){
    aNode.currentBoard.board[aNode.currentBoard.emptyI][aNode.currentBoard.emptyK] = aNode.currentBoard.board[aNode.currentBoard.emptyI][aNode.currentBoard.emptyK+1];
    aNode.currentBoard.board[aNode.currentBoard.emptyI][aNode.currentBoard.emptyK+1] = 0;
    //int toSwitch = aNode.currentBoard.board[aNode.currentBoard.emptyI][aNode.currentBoard.emptyK+1];
    //int oldEmptyI =  aNode.currentBoard.emptyI;
    //int oldEmptyK = aNode.currentBoard.emptyK;
    aNode.currentBoard.emptyK++;
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
    int toSwitch = aNode.currentBoard.board[aNode.currentBoard.emptyI][aNode.currentBoard.emptyK-1];
    int oldEmptyI =  aNode.currentBoard.emptyI;
    int oldEmptyK = aNode.currentBoard.emptyK;

    node returnNode;
    returnNode.currentBoard = aNode.currentBoard;

    returnNode.currentBoard.emptyI = oldEmptyI;
    returnNode.currentBoard.emptyK = oldEmptyK-1;
    returnNode.currentBoard.board[oldEmptyI][oldEmptyK] = toSwitch;
    returnNode.currentBoard.board[oldEmptyI][oldEmptyK-1] = 0;
    returnNode.pathCost = aNode.pathCost+1;
    returnNode.previousMove = 'L';

    return returnNode;
}

node getNeighborU(node aNode){
    int toSwitch = aNode.currentBoard.board[aNode.currentBoard.emptyI-1][aNode.currentBoard.emptyK];
    int oldEmptyI =  aNode.currentBoard.emptyI;
    int oldEmptyK = aNode.currentBoard.emptyK;

    node returnNode;
    returnNode.currentBoard = aNode.currentBoard;

    returnNode.currentBoard.emptyI = oldEmptyI-1;
    returnNode.currentBoard.emptyK = oldEmptyK;
    returnNode.currentBoard.board[oldEmptyI][oldEmptyK] = toSwitch;
    returnNode.currentBoard.board[oldEmptyI-1][oldEmptyK] = 0;
    returnNode.pathCost = aNode.pathCost+1;
    returnNode.previousMove = 'U';

    return returnNode;

}


node getNeighborD(node aNode){
    int toSwitch = aNode.currentBoard.board[aNode.currentBoard.emptyI+1][aNode.currentBoard.emptyK];
    int oldEmptyI =  aNode.currentBoard.emptyI;
    int oldEmptyK = aNode.currentBoard.emptyK;

    node returnNode;
    returnNode.currentBoard = aNode.currentBoard;

    returnNode.currentBoard.emptyI = oldEmptyI+1;
    returnNode.currentBoard.emptyK = oldEmptyK;
    returnNode.currentBoard.board[oldEmptyI][oldEmptyK] = toSwitch;
    returnNode.currentBoard.board[oldEmptyI+1][oldEmptyK] = 0;
    returnNode.pathCost = aNode.pathCost+1;
    returnNode.previousMove = 'D';

    return returnNode;
    
}

int getManhattanScore(int aboard[BOARDSIZE][BOARDSIZE]){
    int manhattanSum = 0;

    for(int i =0;i<BOARDSIZE;i++){
        for(int k=0;k<BOARDSIZE;k++){
            int currentValue = aboard[i][k];
            if(currentValue != 0){
                manhattanSum = manhattanSum+ abs(successMapI[currentValue]-i) +abs(successMapK[currentValue] -k);
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
                    numMisplaced = numMisplaced+1;
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

    totalNum = totalNum << 4;
    totalNum = totalNum+pathCost;

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


board createRandomBoard(int possibleValues[BOARDSIZE*BOARDSIZE]){

    int maxVal = BOARDSIZE*BOARDSIZE;

    vector<int> theList;

    for(int i=0;i<(BOARDSIZE*BOARDSIZE);i++){
        theList.push_back(possibleValues[i]);
    }

    board newboard;

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