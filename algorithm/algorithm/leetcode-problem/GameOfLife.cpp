#include <vector>
#include <iostream>

using namespace std;
/*
Game of Life

According to Wikipedia's article: "The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970."
The board is made up of an m x n grid of cells, where each cell has an initial state: live (represented by a 1) or dead (represented by a 0). Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules (taken from the above Wikipedia article):
Any live cell with fewer than two live neighbors dies as if caused by under-population.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by over-population.
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

1. Set up variables m and n for the grid dimensions and create next_state to store the next generation of the grid.
2. Use directions = {-1,0,1} to simplify the calculation of all neighboring cells. 'directions' helps efficiently locate all neighboring cells for each cell in the grid.
3. Loop through each cell (i,j) in the grid. For each cell, use directions to calculate the positions of all eight neighbors and count the number of live neighbors.
4. Determine the next state of each cell based on its live neighbors:
	Die if fewer than 2 or more than 3 live neighbors.
	Stay alive with 2 or 3 live neighbors.
	Come to life if exactly 3 live neighbors.
5. Replace the current grid with next_state after processing all cells.
*/
void gameOfLife(vector<vector<int>>& board) {
	int m = board.size(), n = board[0].size();
	vector<vector<int>> next_state(m, vector<int>(n, 0));
	vector<int> directions = { -1,0,1 };

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			int live_neighbors = 0;

			for (int x : directions) {
				for (int y : directions) {
					if (x == 0 && y == 0) continue;
					int ni = i + x;
					int nj = j + y;
					if (ni >= 0 && ni < m && nj >= 0 && nj < n) {
						live_neighbors += board[ni][nj];
					}
				}
			}

			if (live_neighbors == 1) 
			{
				if (live_neighbors < 2 || live_neighbors>3) {
					next_state[i][j] = 0;
				}
				else
				{
					next_state[i][j] = 1;
				}
			}
			else
			{
				if (live_neighbors == 3) {
					next_state[i][j] = 1;
				}
			}

		}
	}

	board = next_state;
}

int mainGameOfLife() {
	vector<vector<int>> board = {
		{0, 1, 0},
		{0, 0, 1},
		{1, 1, 1},
		{0, 0, 0}
	};

	cout << "Initial State:" << endl;
	for (const auto& row : board) {
		for (int cell : row) {
			cout << cell << " ";
		}
		cout << endl;
	}

	// Apply the Game of Life rules
	gameOfLife(board);

	// Output the next state
	cout << "\nNext State:" << endl;
	for (const auto& row : board) {
		for (int cell : row) {
			cout << cell << " ";
		}
		cout << endl;
	}

	return 0;
}