#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define BOARDSIZE 3





typedef struct node {
    int pathCost;
    struct board *currentBoard;
    char boardHash[20];
} Node;

typedef struct Board {
    int board[BOARDSIZE][BOARDSIZE];
} board;


void printArray(int aboard[BOARDSIZE][BOARDSIZE]);



board *aBoard;
board *successBoard;


int main() {

   aBoard = (board*) malloc(sizeof(board));
   successBoard = (board*) malloc(sizeof(board));

    int boardSize = 3;
    int count =0;
    for(int i=0;i<BOARDSIZE;i++){
        for(int k = 0;k<BOARDSIZE;k++){
            aBoard->board[i][k] = count;
            count = count+1;
        }
    }

    printArray(aBoard->board);



    return 0;
}

void printArray(int aboard[BOARDSIZE][BOARDSIZE]){
    printf("\n");
    for(int i =0;i<BOARDSIZE;i++){
        for(int k=0;k<BOARDSIZE;k++){
            printf("%d ", aboard[i][k]);
        }
        printf("\n");
    }
}