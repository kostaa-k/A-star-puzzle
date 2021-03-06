#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "hashset.h"

#define BOARDSIZE 3
#define MAXHASHSIZE 

typedef struct Board {
    int board[BOARDSIZE][BOARDSIZE];
    int emptyI;
    int emptyK;
} board;



typedef struct Node {
    int pathCost;
    board currentBoard;
    char boardHash[20];
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

char *getBoardHash(node);

int DFS(node, int);
void idaStar(node);

int getManhattanScore(node aNode);

board *aBoard;
successboard *successState;

int successMapI[BOARDSIZE*BOARDSIZE];
int successMapK[BOARDSIZE*BOARDSIZE];

hashset_t set;


int main() {

    set = hashset_create();

    if (set == NULL) {
        fprintf(stderr, "failed to create hashset instance\n");
        abort();
    }

   board aBoard;
   successState = (successboard*) malloc(sizeof(successboard));

    int boardSize = 3;
    int count =0;
    for(int i=0;i<BOARDSIZE;i++){
        for(int k = 0;k<BOARDSIZE;k++){
            aBoard.board[i][k] = count;
            successMapI[count] = i;
            successMapK[count] = k;
            count = count+1;
        }
    }
    

    //printBoard(aBoard.board);

    node *startNode = (node*) malloc(sizeof(node));
    startNode->currentBoard = aBoard;
    startNode->currentBoard.emptyI = 0;
    startNode->currentBoard.emptyK = 0;
    startNode->pathCost = 0;

    node rNeighbor = getNeighborR(*startNode);


    node lNeighbor = getNeighborL(*startNode);

    node uNeighbor = getNeighborU(*startNode);

    node dNeighbor = getNeighborD(*startNode);

    //printf("manhattan score: %d\n", getManhattanScore(rNeighbor));

    printf(getBoardHash(dNeighbor));

    //idaStar(rNeighbor);


    return 0;
}



void idaStar(node tempNode){

    int depth=0;

    int result = DFS(tempNode, 40);

    // while(depth < 60){
    //     int result = DFS(tempNode, depth);
    //     depth = depth+1;
    //     printf("Depth: %d\n", depth);
    // }
}

int DFS(node theNode, int limit){
    //printBoard(theNode.currentBoard.board);
    //printf("Path cost: %d\n", theNode.pathCost);
    //printf("manhattan cost: %d\n", getManhattanScore(theNode));

    //hashset_add()
    if(theNode.pathCost+getManhattanScore(theNode) > limit){
        return theNode.pathCost;
    }

    if(theNode.previousMove != 'R' && theNode.currentBoard.emptyK > 0){
        node lNode = getNeighborL(theNode);
        int answer = DFS(lNode, limit);

    }
    if(theNode.previousMove != 'L' && theNode.currentBoard.emptyK < (BOARDSIZE-1)){
        node rNode = getNeighborR(theNode);
        if(rNode.pathCost > 0){
            int answer = DFS(rNode, limit);
        }
    }
    if(theNode.previousMove != 'D' && theNode.currentBoard.emptyI > 0){
        node uNode = getNeighborU(theNode);
        int answer = DFS(uNode, limit);

        
    }
    if(theNode.previousMove != 'U' && theNode.currentBoard.emptyI < (BOARDSIZE-1)){
        //node dNode = getNeighborD(theNode);
        int answer = DFS(getNeighborD(theNode), limit);
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

int getManhattanScore(node aNode){
    int manhattanSum = 0;

    for(int i =0;i<BOARDSIZE;i++){
        for(int k=0;k<BOARDSIZE;k++){
            int currentValue = aNode.currentBoard.board[i][k];
            if(currentValue != 0){
                //printf("Value were looking at: %d\n", currentValue);
                //printf("Value score: %d\n", abs(successMapI[currentValue]-i) +abs(successMapK[currentValue] -k));

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

char *getBoardHash(node aNode){

    char theString[17];
    int strCount = 0
    for(int i=0;i<BOARDSIZE;i++){
        for(int k=0;k<BOARDSIZE;k++){
            char stringValue[1];
            itoa(aNode.currentBoard.board[i][k], stringValue, 10);
            theString[strCount] = stringValue;

        }
    }

    return *theString;

}