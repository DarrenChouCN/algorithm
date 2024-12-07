#include <iostream>
#include <vector>

using namespace std;

/*
Valid Sudoku
Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:
Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.

1.Row Check: Create a 9*9 boolean array row[9][9] where row[i][num-1] indicates whether the digit num has already appeared in the i-th row.
2.Column Check: Create a 9*9 boolean array column[9][9] where column[j][num-1] indicates whether the digit num has already appeared in the j-th column.
3.Sub-box Check: Create a 9*9 boolean array subbox[9][9] where subbox[box_index][num-1] indicates whether digit num has already appeared in the box_index sub-box. The box_index is calculated by (i/3)*3+(j/3)
*/

bool isValidSudoku(vector<vector<char>>& board) {
	bool row[9][9] = { false };
	bool column[9][9] = { false };
	bool subbox[9][9] = { false };

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++) {
			if (board[i][j] != '.')
			{
				int num = board[i][j] - '1';
				int boxIndex = (i / 3) * 3 + (j / 3);

				if (row[i][num] || column[j][num] || subbox[boxIndex][num])
				{
					return false;
				}

				row[i][num] = true;
				column[j][num] = true;
				subbox[boxIndex][num] = true;
			}
		}
	}
	return true;
}

int mainIsValidSudoku() {
    // Test Case 1: Valid Sudoku
    vector<vector<char>> board1 = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'9','8','.','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };

    // Test Case 2: Invalid Sudoku
    vector<vector<char>> board2 = {
        {'8','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'9','8','.','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };

    cout << "Test Case 1 - Expected: true, Actual: " << (isValidSudoku(board1) ? "true" : "false") << endl;
    cout << "Test Case 2 - Expected: false, Actual: " << (isValidSudoku(board2) ? "true" : "false") << endl;

    return 0;
}