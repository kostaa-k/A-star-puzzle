#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <bits/stdc++.h> 
#include<iostream> 
#include <sstream>  // for string streams 
#include <string>


#define BOARDSIZE 4

using namespace std;

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

node getNeighborR(node);
node getNeighborL(node);
node getNeighborU(node);
node getNeighborD(node);

//getBoardHash(int[BOARDSIZE][BOARDSIZE]);


int DFS(node, int);
void idaStar(node);

int getManhattanScore(int[BOARDSIZE][BOARDSIZE]);

board *aBoard;
successboard *successState;

int successMapI[BOARDSIZE*BOARDSIZE];
int successMapK[BOARDSIZE*BOARDSIZE];

unordered_set <uint64_t> visitedNodes;

bool isBoardSolved(int[BOARDSIZE][BOARDSIZE]);

uint64_t getBoardHash(int[BOARDSIZE][BOARDSIZE], int);

int findKValue(int[BOARDSIZE][BOARDSIZE], int);
int findIValue(int[BOARDSIZE][BOARDSIZE], int);

//int getBoardHash(int listOfNums[3]);

int countNodes =0;

int main() {


   board aBoard;
   successState = (successboard*) malloc(sizeof(successboard));

    string boardStr = "13.2.10.3.1.12.8.4.5.0.9.6.15.14.11.7";
    int thisBoard[] = {13,2,10,3,1,12,8,4,5,0,9,6,15,14,11,7};
    int thisBoard2[] = {1,10,15,4,13,6,3,8,2,9,12,7,14,5,0,11};
    int successBoard[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};

    int count =0;
    for(int i=0;i<BOARDSIZE;i++){
        for(int k = 0;k<BOARDSIZE;k++){
            //aBoard.board[i][k] = count;
            aBoard.board[i][k] = thisBoard2[count];
            successMapI[successBoard[count]] = i;
            successMapK[successBoard[count]] = k;
            count = count+1;
        }
    }



    node startNode;
    startNode.currentBoard= aBoard;
    startNode.currentBoard.emptyI = findIValue(startNode.currentBoard.board, 0);
    startNode.currentBoard.emptyK = findKValue(startNode.currentBoard.board, 0);
    startNode.pathCost = 0;
    startNode.previousMove='N';

    //string hashValue = getBoardHash(rNeighbor.currentBoard.board)
    idaStar(startNode);

    //getBoardHash(rNeighbor);


    return 0;
}



void idaStar(node tempNode){

    int depth=0;
    visitedNodes.clear();

    int result = 100;
    while(depth < 50 && result >= 0){
        result = DFS(tempNode, depth);
        depth = depth+1;

        visitedNodes.clear();

        cout << "Searched depth: ";
        cout << depth;
    }

    if(result < 0){
        cout << "FOUND RESULT in steps: \n";
        cout << result*-1;
        cout << "\n";
        cout << "DEPTH IS:";
        cout << depth;
    }
    
    cout << "\n";
    cout << "Count of Nodes searched:\n";
    cout << countNodes;

}

int DFS(node theNode, int limit){
    if(theNode.pathCost+getManhattanScore(theNode.currentBoard.board) > limit){
        return theNode.pathCost;
    }
    countNodes = countNodes+1;
    uint64_t value = getBoardHash(theNode.currentBoard.board, theNode.pathCost);
    if(visitedNodes.find(value) == visitedNodes.end()){
        visitedNodes.insert(value);
        countNodes = countNodes+1;
    }
    else{
        return 1;
    }

    if(isBoardSolved(theNode.currentBoard.board)){
        cout << "SOLVED!";
        cout << "\n";
        printBoard(theNode.currentBoard.board);
        return -theNode.pathCost;
    }

    if(theNode.previousMove != 'R' && theNode.currentBoard.emptyK > 0){
        node lNode = getNeighborL(theNode);
        int answer = DFS(lNode, limit);
        if(answer < 0){
            return answer;
        }

    }
    if(theNode.previousMove != 'L' && theNode.currentBoard.emptyK < (BOARDSIZE-1)){
        node rNode = getNeighborR(theNode);
        int answer = DFS(rNode, limit);
        if(answer < 0){
            return answer;
        }
        
    }
    if(theNode.previousMove != 'D' && theNode.currentBoard.emptyI > 0){
        node uNode = getNeighborU(theNode);
        int answer = DFS(uNode, limit);
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
    int toSwitch = aNode.currentBoard.board[aNode.currentBoard.emptyI][aNode.currentBoard.emptyK+1];
    int oldEmptyI =  aNode.currentBoard.emptyI;
    int oldEmptyK = aNode.currentBoard.emptyK;

    node returnNode;
    returnNode.currentBoard = aNode.currentBoard;

    returnNode.currentBoard.emptyI = oldEmptyI;
    returnNode.currentBoard.emptyK = oldEmptyK+1;
    returnNode.currentBoard.board[oldEmptyI][oldEmptyK] = toSwitch;
    returnNode.currentBoard.board[oldEmptyI][oldEmptyK+1] = 0;
    returnNode.pathCost = aNode.pathCost+1;
    returnNode.previousMove = 'R';

    return returnNode;
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