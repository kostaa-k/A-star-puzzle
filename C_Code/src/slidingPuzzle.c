#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define BOARDSIZE 3

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

int DFS(node, int);
void idaStar(node);

int getManhattanScore(node aNode);

board *aBoard;
successboard *successState;

int successMapI[BOARDSIZE*BOARDSIZE];
int successMapK[BOARDSIZE*BOARDSIZE];


int main() {

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

    //printf("Path cost: %d\n", rNeighbor.pathCost);

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
    if(theNode.pathCost+getManhattanScore(theNode) > limit){
        return theNode.pathCost;
    }

    if(theNode.previousMove != 'R'){
        node lNode = getNeighborL(theNode);
        if(lNode.pathCost > 0){
            int answer = DFS(lNode, limit);
        }
    }
    if(theNode.previousMove != 'L'){
        node rNode = getNeighborR(theNode);
        if(rNode.pathCost > 0){
            int answer = DFS(rNode, limit);
        }
    }
    if(theNode.previousMove != 'D'){
        node uNode = getNeighborU(theNode);
        if(uNode.pathCost > 0){
            int answer = DFS(uNode, limit);
        }
        
    }
    if(theNode.previousMove != 'U'){
        node dNode = getNeighborD(theNode);
        if(dNode.pathCost > 0){
            int answer = DFS(dNode, limit);
        }
    }

    return limit;
}


node getNeighborR(node aNode){
    if( aNode.currentBoard.emptyK < (BOARDSIZE-1)){
        int toSwitch = aNode.currentBoard.board[aNode.currentBoard.emptyI][aNode.currentBoard.emptyK+1];
        int oldEmptyI =  aNode.currentBoard.emptyI;
        int oldEmptyK = aNode.currentBoard.emptyK;

        board newBoard;

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
    else{
        node fakeNode;
        fakeNode.pathCost = -100;
        return fakeNode;
    }
}


node getNeighborL(node aNode){
    if( aNode.currentBoard.emptyK > 0){
        int toSwitch = aNode.currentBoard.board[aNode.currentBoard.emptyI][aNode.currentBoard.emptyK-1];
        int oldEmptyI =  aNode.currentBoard.emptyI;
        int oldEmptyK = aNode.currentBoard.emptyK;

        // printf("HERE!");

        board newBoard;

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
    else{
        node fakeNode;
        fakeNode.pathCost = -100;
        return fakeNode;
    }
}

node getNeighborU(node aNode){
    if( aNode.currentBoard.emptyI > 0){
        int toSwitch = aNode.currentBoard.board[aNode.currentBoard.emptyI-1][aNode.currentBoard.emptyK];
        int oldEmptyI =  aNode.currentBoard.emptyI;
        int oldEmptyK = aNode.currentBoard.emptyK;

        // printf("HERE!");

        board newBoard;

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
    else{
        node fakeNode;
        fakeNode.pathCost = -100;
        return fakeNode;
    }
}


node getNeighborD(node aNode){
    if( aNode.currentBoard.emptyI < (BOARDSIZE-1)){
        int toSwitch = aNode.currentBoard.board[aNode.currentBoard.emptyI+1][aNode.currentBoard.emptyK];
        int oldEmptyI =  aNode.currentBoard.emptyI;
        int oldEmptyK = aNode.currentBoard.emptyK;

        // printf("HERE!");

        board newBoard;

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
    else{
        node fakeNode;
        fakeNode.pathCost = -100;
        return fakeNode;
    }
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
