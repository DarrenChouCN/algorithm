## N-Queens
The N-Queens problem is a classic combinatorial problem where the task is to place N queens on an N x N chessboard such that no two queens threaten each other. This means that no two queens can be placed in the same row, column, or diagonal. The goal is to find all possible valid configurations of placing the queens on the board.
1. Given an integer N, return all distinct solutions to the N-Queens problem.
2. A queen can attack another queen if they are placed in the same row, column, or along any diagonal.
3. The output should be a list of all valid board configurations where a 'Q' represents a queen and '.' represents an empty space.

Thought Process:
1. Traverse each column in the current row.
2. Evaluate if the current row and column meet the conditions: 
    1) The column is not occupied. 
	2) The '\' diagonal is clear. 
	3) The '/' diagonal is clear. 
    4) If conditions are not met, move to the next column. If met, mark the current column and continue recursively with the next row, "selecting" this column for further exploration.
3. Repeat the process until reaching the last row, then add the current valid configuration to solutions.
4. Once a solution is found, backtrack to the previous row to explore other column possibilities.
5. Complete search: Each row and column will be fully searched for valid solutions and added to solutions until the entire search is finished.

Time and Space Complexity: O(N!) and O(N^2)

```cpp
vector<vector<string>> solveNQueens(int n) {
	vector<vector<string>> solutions;

	vector<int> queens(n, -1); // the column positions of queens
	vector<int> columns(n, false); // mark columns as occupied
	vector<int> diagonals1(2 * n - 1, false); // mark '\' diagonals
	vector<int> diagonals2(2 * n - 1, false); // mark '/' diagonals

	backtrack(solutions, queens, n, 0, columns, diagonals1, diagonals2);

	return solutions;
}

void backtrack(vector<vector<string>>& solutions, vector<int>& queens, int n, int row,
	vector<int>& columns, vector<int>& diagonals1, vector<int>& diagonals2) {
	if (row == n) {
		// All queens are placed successfully, add the solution
		vector<string> board = generateBoard(queens, n);
		solutions.push_back(board);
		return;
	}

	for (int col = 0; col < n; col++)
	{
		if (columns[col] || diagonals1[row - col + n - 1] || diagonals2[row + col]) {
			continue;
		}

		// Place queen at (row, col)
		queens[row] = col;
		columns[col] = true;
		diagonals1[row - col + n - 1] = true;
		diagonals2[row + col] = true;

		// Recurse to place queen in the next row
		backtrack(solutions, queens, n, row + 1, columns, diagonals1, diagonals2);

		// Backtrack: remove the queen and reset the flags
		queens[row] = -1;
		columns[col] = false;
		diagonals1[row - col + n - 1] = false;
		diagonals2[row + col] = false;
	}
}

vector<string> generateBoard(vector<int>& queens, int n) {
	vector<string> board(n, string(n, '.'));
	for (int i = 0; i < n; i++)
		board[i][queens[i]] = 'Q';
	return board;
}
```

## N-Queens (Bit Manipulation)
1. ((1 << n) - 1) & ~(columns | diagonals1 | diagonals2):
	a. ((1 << n) - 1) generates a binary number with n bits all set to 1.
	b. ~(columns | diagonals1 | diagonals2) takes the current positions where 1 has been placed (through OR operations) and inverts them. The positions where the inverted value has 1 represent the locations where a queen can be placed.
	c. The result of the AND operation between these two determines the positions (where the binary representation has 1) that are available for placing a queen.
2. availablePositions & -availablePositions:
	Using two's complement (invert the bits and add 1, with the highest bit set to 1), performing a bitwise AND between availablePositions and its negative binary form yields a new binary number with the lowest 1 bit (not necessarily the rightmost bit). This value is stored as position.
3. availablePositions - 1:
	Since subtraction borrows 1 from the lowest 1 bit, it turns that bit to 0. Then, performing a bitwise AND with the original availablePositions clears the lowest 1 bit, marking the position as occupied.
4. Move to row + 1. Perform a bitwise OR operation between columns, diagonals1, diagonals2, and position to update available positions for the next row. Shift the main diagonal (diagonals1) left by 1 and the anti-diagonal (diagonals2) right by 1.
5. The recursion and loop accumulate the final valid configurations.

Although the complexity remains unchanged, the actual execution time and the required memory are greatly reduced. The speed of bitwise operations is relatively fast, and only a single binary string is needed to represent a storage state. This is much faster compared to using two arrays.

Time and Space Complexity: O(N!) and O(N^2)

```cpp
vector<vector<string>> solveNQueens(int n) {
	vector<vector<string>> solutions;
	vector<int> queens(n, -1);
	solve(0, 0, 0, 0, n, queens, solutions);
	return solutions;
}

void solve(int row, int columns, int diagonals1, int diagonals2, int n, vector<int>& queens, vector<vector<string>>& solutions) {
	if (row == n) {
		solutions.push_back(generateBoard(queens, n));
		return;
	}

	int availablePositions = ((1 << n) - 1) & ~(columns | diagonals1 | diagonals2);

	while (availablePositions) {
		int position = availablePositions & -availablePositions;
		availablePositions &= (availablePositions - 1);

		int columnIndex = __builtin_ctz(position);
		queens[row] = columnIndex;

		solve(row + 1,
			columns | position,
			(diagonals1 | position) << 1,
			(diagonals2 | position) >> 1,
			n, queens, solutions);

		queens[row] = -1;
	}
}
```