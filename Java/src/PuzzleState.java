import java.util.HashMap;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.lang.Math;
import java.util.Arrays;

public class PuzzleState
{ 
	public int heuristicScore;
	public int pathCost;
	public int[][] board;
	private PuzzleState lastNode;
	public int emptySpotI;
	public int emptySpotK;
	public int totalScore;

	public PuzzleState(int pathCost, PuzzleState lastNode, int[][] board, int emptySpotI, int emptySpotK){
		this.lastNode = lastNode;
		this.pathCost = pathCost;
		this.board = board;
		this.emptySpotI = emptySpotI;
		this.emptySpotK = emptySpotK;
	}

	public int getTotalScore(){
		return this.totalScore;
	}

	public void setTotalScore(Map<Integer, List<Integer>> successDictionary){
		this.heuristicScore = getManhattanDistance(successDictionary);
		this.totalScore = this.heuristicScore+this.pathCost;
	}

	public int getManhattanDistance(Map<Integer, List<Integer>> successDictionary){

		int manhattanSum = 0;
		for (int i =0; i< board.length;i++){
			for (int k=0; k< board.length;k++){
				if(board[i][k] != 0){
					List<Integer> otherValues = successDictionary.get(board[i][k]);
					manhattanSum = manhattanSum+Math.abs(otherValues.get(0)-i)+Math.abs(otherValues.get(1)-k);
				}
			}
		}

		return manhattanSum;
	}

	public List<PuzzleState> getNeighbors(List<List<Integer>> possibleMoves){
		int emptyTileI = this.emptySpotI;
		int emptyTileK = this.emptySpotK;

		int tempTile = this.board[emptyTileI][emptyTileK];


		List<PuzzleState> outputList = new ArrayList<>();

		for(List<Integer> move: possibleMoves){
			int moveI = move.get(0)+emptyTileI;

			if(moveI >= 0 && moveI < this.board.length){
				int moveK = move.get(1)+emptyTileK;
				if(moveK >= 0 && moveK < this.board.length){
					int[][] tempBoard = deepCopy(this.board);

					tempBoard[emptyTileI][emptyTileK] = tempBoard[moveI][moveK];
					tempBoard[moveI][moveK] = tempTile;

					PuzzleState tempObject = new PuzzleState(this.pathCost+1, this, deepCopy(tempBoard), moveI, moveK);

					outputList.add(tempObject);
				}
			}

		}

		return outputList;
	}

	public static int[][] deepCopy(int[][] original) {
		if (original == null) {
			return null;
		}
	
		final int[][] result = new int[original.length][];
		for (int i = 0; i < original.length; i++) {
			result[i] = Arrays.copyOf(original[i], original[i].length);
			// For Java versions prior to Java 6 use the next:
			// System.arraycopy(original[i], 0, result[i], 0, original[i].length);
		}
		return result;
	}

	public void printBoardNicely(int[][] board){

		for(int i=0;i<board.length;i++){
            for(int k=0;k<board.length;k++){
                System.out.print(board[i][k]+" ");
            }
            System.out.println();
        }
	}

	public String boardToHash(){
		return this.boardToStr()+String.valueOf(this.pathCost);
	}

	public String boardToStr(){

        String outputStr = "";
        for (int i =0; i<this.board.length;i++){
            for(int k=0;k<this.board.length;k++){
                outputStr = outputStr+"."+String.valueOf(this.board[i][k]);
            }
        }

        return outputStr;
    }

}