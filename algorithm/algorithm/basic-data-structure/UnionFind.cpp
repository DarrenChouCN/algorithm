#include <unordered_map>
#include <vector>
#include <iostream>
#include "BasicDataStructure.h"


using namespace std;

/*
Number of Provinces

https://leetcode.com/problems/friend-circles/

There are n cities. Some of them are connected, while some are not. If city a is connected directly with city b, and city b is connected directly with city c, then city a is connected indirectly with city c.
A province is a group of directly or indirectly connected cities and no other cities outside of the group.
You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith city and the jth city are directly connected, and isConnected[i][j] = 0 otherwise.
Return the total number of provinces.

1. Matrix Symmetry: Since city connections form an undirected graph, the matrix isConnected is symmetric. Only half of the matrix needs to be traversed, reducing redundant checks.
2. Connected Components: Cities are viewed as connected components in an undirected graph, where each component represents a province. Union-Find efficiently merges directly or indirectly connected cities into the same component.
3. Union-Find Efficiency: With path compression and union by rank, Union-Find operations are nearly constant, keeping the algorithm efficient even for large inputs.

Time and Space Complexity: Traversing half of the matrix gives O(N^2) time complexity, while Union-Find¡¯s space complexity is O(N).
*/
int findCircleNum(vector<vector<int>>& isConnected) {
	int N = isConnected.size();
	UnionFindArray unionFind(N);

	for (int i = 0; i < N; i++)
		for (int j = i + 1; j < N; j++)
			if (isConnected[i][j] == 1)
				unionFind.unionSets(i, j);

	return unionFind.getSetCount();
}


/*
Number of Islands

https://leetcode.com/problems/number-of-islands/

Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.
*/

/*
Recursion: This approach is suitable for smaller grids, as the recursion depth may lead to stack overflow in cases with large input sizes.

Time and Space Complexity : O(M*N) and O(M*N)
*/
void infect(vector<vector<char>>& grid, int i, int j) {
	int rows = grid.size();
	int cols = grid[0].size();

	// Base Case
	if (i < 0 || i >= rows || j < 0 || j >= cols || grid[i][j] != '1')
		return;

	grid[i][j] = '0';

	// Recursively infect adjacent cells
	infect(grid, i - 1, j);
	infect(grid, i + 1, j);
	infect(grid, i, j - 1);
	infect(grid, i, j + 1);
}

int numIslandsRecursion(vector<vector<char>>& grid) {
	int rows = grid.size();
	if (rows == 0) return 0;
	int cols = grid[0].size();

	int islands = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (grid[i][j] == '1') {
				islands++;
				infect(grid, i, j);
			}

	return islands;
}

int numIslands(vector<vector<char>>& grid) {
	int rows = grid.size();
	if (rows == 0) return 0;
	int cols = grid[0].size();

	UnionFindArray unionFind(rows, cols);
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < cols; c++)
			if (grid[r][c] == '1') {
				int index = unionFind.getIndex(r, c);
				unionFind.parent[index] = index;
				unionFind.numSets++;
			}

	for (int j = 1; j < cols; j++) {
		if (grid[0][j - 1] == '1' && grid[0][j] == '1') {
			unionFind.unionSets(0, j - 1, 0, j);
		}
	}

	for (int i = 1; i < rows; i++) {
		if (grid[i - 1][0] == '1' && grid[i][0] == '1') {
			unionFind.unionSets(i - 1, 0, i, 0);
		}
	}

	for (int i = 1; i < rows; i++)
		for (int j = 1; j < cols; j++)
			if (grid[i][j] == '1') {
				if (grid[i - 1][j] == '1') {
					unionFind.unionSets(i - 1, j, i, j);
				}
				if (grid[i][j - 1] == '1') {
					unionFind.unionSets(i, j - 1, i, j);
				}
			}

	return unionFind.getSetCount();
}

/*
Number of Islands II
A 2D grid map of m rows and n columns is initially filled with water. We may perform an addLand operation which turns the water at position (row, col) into a land. Given a list of positions to operate, count the number of islands after each addLand operation. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

The main difference between numIslands2 and numIslands1 lies in the dynamic nature of the problem. In numIslands1, the islands are counted in a static grid where all land cells are predefined. In contrast, numIslands2 involves a dynamic grid where water cells are incrementally turned into land, requiring island count updates after each operation.

In this connect implementation, a cell (r, c) is first converted to a 1D index. If the cell is water (indicated by size[index] == 0), it¡¯s marked as land by setting its parent to itself, initializing its size to 1, and incrementing the island count (numSets++). Then, it attempts to merge with any adjacent land cells by calling unionSets on its four neighbors. Finally, it returns the updated number of islands (numSets).

Time and Space Complexity : O(k¡Á¦Á(N)) and O(M*N)
*/
vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
	UnionFindArray unionFind(m, n);
	unionFind.setDynamicArray();
	vector<int> result;
	for (const auto& position : positions) {
		int numSets = unionFind.connect(position[0], position[1]);
		result.push_back(numSets);
	}
	return result;
}

int mainNumIslands2() {
	int m = 3, n = 3;
	vector<vector<int>> positions = { {0, 0}, {0, 1}, {1, 2}, {2, 1} };

	vector<int> result = numIslands2(m, n, positions);

	cout << "Number of islands after each operation: ";
	for (int count : result) {
		cout << count << " ";
	}
	cout << endl;
	cout << "Expected output: 1 1 2 3" << endl;

	return 0;
}