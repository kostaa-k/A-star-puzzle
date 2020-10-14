import java.util.HashMap;
import java.util.HashSet;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.lang.Math;

import java.util.Comparator;
import java.util.PriorityQueue;


public class mainTest {
    public static int minValue = 1000;
    public static HashSet<String> visitedNodes = new HashSet<>();

    public static void main(String[] args) {
        System.out.println("Hello world");
        
        int boardSize = 4;
        
        int[][] aBoard = new int[boardSize][boardSize];

        ArrayList<Integer> possibleValues = new ArrayList<>();

        for(int i=1;i<boardSize*boardSize;i++){
            possibleValues.add(i);
        }
        possibleValues.add(0);

        int[][] successBoard = createBoardFromList(possibleValues);

        Map<Integer, List<Integer>> successMap = getSuccessHashMap(successBoard);

        String boardStr = "13.2.10.3.1.12.8.4.5.0.9.6.15.14.11.7";
        String boardStr2 = "1.10.15.4.13.6.3.8.2.9.12.7.14.5.0.11";
        String boardStr3 = "1.2.6.3.4.5.10.7.8.9.14.11.12.13.0.15";

        int[][] theBoard = createBoardFromStr(boardStr3);

        printBoardNicely(theBoard);
        System.out.println("");

        Map<Integer, List<Integer>> boardMap = getSuccessHashMap(theBoard);
        List<Integer> zerPosition = boardMap.get(0);

        PuzzleState startState = new PuzzleState(0, null, theBoard, zerPosition.get(0), zerPosition.get(1));

        List<PuzzleState> connectedStates = startState.getNeighbors(getPossibleMoves());

        System.out.println("");
        System.out.println(connectedStates.size());

        // for(PuzzleState state: connectedStates){
        //     printBoardNicely(state.board);
        //     System.out.println(String.valueOf(state.emptySpotI)+ ", "+String.valueOf(state.emptySpotK));
        //     System.out.println("");
        //     for(PuzzleState state2: state.getNeighbors(getPossibleMoves())){
        //         printBoardNicely(state2.board);
        //         System.out.println(String.valueOf(state2.emptySpotI)+ ", "+String.valueOf(state2.emptySpotK));
        //         System.out.println();
        //     }
        // }

        idaStar(startState, boardToStr(successBoard), getPossibleMoves(), getSuccessHashMap(successBoard));
        //BFS(startState, boardToStr(successBoard), getPossibleMoves(), getSuccessHashMap(successBoard));
        
    }



    public static void idaStar(PuzzleState aNode, String successStr, List<List<Integer>> possibleMoves, Map<Integer, List<Integer>> successDictionary){
        int depth = 1;
        System.out.println(successStr);
        int result = 100;

        while(result > 0 && depth < 75){
            visitedNodes.clear();
            System.out.println(depth);
            result = DFS(aNode, depth, successStr, possibleMoves, successDictionary);
            //System.out.println(depth);
            System.out.println("Result is: "+ String.valueOf(result));
            minValue = 1000;
            depth = result;
        }
        
    }

    public static int DFS(PuzzleState node, int limit, String successStr, List<List<Integer>> possibleMoves, Map<Integer, List<Integer>> successDictionary){

        if(boardToStr(node.board).equals(successStr)){
            return -1*(node.pathCost);
        }

        if(node.getTotalScore() > limit){
            return node.getTotalScore();
        }

        for(PuzzleState neighborNode: node.getNeighbors(possibleMoves)){
            if(!visitedNodes.contains((neighborNode.boardToHash()))){
                visitedNodes.add((neighborNode.boardToHash()));
                neighborNode.setTotalScore(successDictionary);
                int answer =  DFS(neighborNode, limit, successStr, possibleMoves, successDictionary);
                if(answer < 0){
                    return answer;
                }
                if(answer < minValue){
                    minValue = answer;
                }
                
            }
        }

        

        return minValue;
    }


    public static void BFS(PuzzleState node, String successStr, List<List<Integer>> possibleMoves, Map<Integer, List<Integer>> successDictionary){
        HashSet<String> visitedNodes = new HashSet<>();

        Comparator<PuzzleState> aComparator = new Comparator<PuzzleState>() {
            @Override
            public int compare(PuzzleState s1, PuzzleState s2) {
                return s1.heuristicScore - s2.heuristicScore;
            }
        };

        PriorityQueue<PuzzleState> frontierNodes = new PriorityQueue<>(aComparator);

        boolean isSolved = false;

        int count = 0;

        while(isSolved == false){

            for(PuzzleState neighborNode: node.getNeighbors(possibleMoves)){
                if(!visitedNodes.contains((neighborNode.boardToHash()))){
                    neighborNode.setTotalScore(successDictionary);
                    int totalScore = neighborNode.getTotalScore();
                    if(totalScore < 80){
                        frontierNodes.add(neighborNode);
                    }
                    visitedNodes.add(neighborNode.boardToHash());
                }
            }

            node = frontierNodes.poll();

            if(boardToStr(node.board).equals(successStr)){
                isSolved = true;
            }

            count = count+1;

            if(count%100000 == 0){
                System.out.println(String.format("# Nodes is: %d , CurrentScore = %d , Depth is: %d", count, node.heuristicScore, node.pathCost));
            }
        }
        System.out.println(String.format("Found answer in %d Moves!", node.pathCost));
        printBoardNicely(node.board);

    }


    public static Map<Integer, List<Integer>> getSuccessHashMap(int[][] successBoard){


        Map<Integer, List<Integer>> returnMap = new HashMap<>();

        for(int i=0;i<successBoard.length;i++){
            for(int k=0;k<successBoard.length;k++){
                List<Integer> aList = new ArrayList<>();
                aList.add(i);
                aList.add(k);
                returnMap.put(successBoard[i][k], aList);
            }
        }

        return returnMap;
    }

    public static String boardToStr(int[][] board){

        String outputStr = "";
        for (int i =0; i<board.length;i++){
            for(int k=0;k<board.length;k++){
                outputStr = outputStr+"."+String.valueOf(board[i][k]);
            }
        }

        return outputStr;
    }


    public static List<List<Integer>> getPossibleMoves(){

        List<List<Integer>> possibleMoves = new ArrayList<>();

        for(int i =-1;i<2;i++){
            for (int k=-1;k<2;k++){
                if(i != k && (i+k) != 0){
                    List<Integer> tempList = new ArrayList<>(2);
                    tempList.add(0, i);
                    tempList.add(1, k);
                    possibleMoves.add(tempList);
                }
            }
        }

        return possibleMoves;
    }



    public static int[][] createBoardFromList(List<Integer> values){

        int boardSize = (int)Math.sqrt(values.size()+1);

        int[][] aBoard = new int[boardSize][boardSize];

        int count =0;
        for(int i=0;i<boardSize;i++){
            for(int k=0;k<boardSize;k++){
                aBoard[i][k] = values.get(count);
                count = count+1;
            }
        }

        return aBoard;
    }

    // public static int[][] createRandomBoard(int boardSize){
    //     int[][] aBoard = new int[boardSize][boardSize];
    //     aBoard[0][0] = 13;
    //     aBoard[0][1] = 2;
    //     aBoard[]
    // }

    public static int[][] createBoardFromStr(String theBoardStr){
        String[] parts = theBoardStr.split("\\.", 0);
        List<Integer> intList = new ArrayList<Integer>(parts.length);
        for(String a: parts){
            intList.add(Integer.parseInt(a));
        }

        System.out.println("Finished loop");

        return createBoardFromList(intList);
    }

    public static void printBoardNicely(int[][] board){

        for(int i=0;i<board.length;i++){
            for(int k=0;k<board.length;k++){
                System.out.print(board[i][k]+" ");
            }
            System.out.println();
        }
	}
}