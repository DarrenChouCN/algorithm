#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> multiplyMatrices(
	vector<vector<int>>& matrix1, vector<vector<int>>& matrix2) {
	int rows = matrix1.size();
	int cols = matrix2[0].size();
	int commonDim = matrix2.size();

	vector<vector<int>> resultMatrix(rows, vector<int>(cols, 0));

	for (int row = 0; row < rows; row++)
		for (int col = 0; col < cols; col++)
			for (int k = 0; k < commonDim; k++)
				resultMatrix[row][col] += matrix1[row][k] * matrix2[k][col];

	return resultMatrix;
}

vector<vector<int>> matrixExponentiation(vector<vector<int>>& matrix, int power) {
	int size = matrix.size();
	vector<vector<int>> identityMatrix(size, vector<int>(size));
	for (int i = 0; i < size; i++)
		identityMatrix[i][i] = 1;

	vector<vector<int>> baseMatrix = matrix;

	for (; power != 0; power >>= 1) {
		if (power & 1) {
			identityMatrix = multiplyMatrices(identityMatrix, baseMatrix);
		}

		baseMatrix = multiplyMatrices(baseMatrix, baseMatrix);
	}

	return identityMatrix;
}


/*
Fibonacci
F(1)=1, F(2)=1, F(n)=F(n-1)+F(n-2)

Proof: Deriving the Matrix for Fibonacci Sequence Using Undetermined Coefficients
The goal is to find a matrix A such that the Fibonacci sequence can be expressed in matrix form:
	V(n) = A * V(n-1)

where the state vector V(n) is defined as:
	V(n) = [ F(n)   ]
		   [ F(n-1) ]

Assume matrix A is of the form:
	A = [ a  b ]
		[ c  d ]

From the Fibonacci recurrence relation: F(n) = F(n-1) + F(n-2)

This results in the matrix equation:
	[ F(n)   ] = [ a  b ] * [ F(n-1) ]
	[ F(n-1) ] = [ c  d ] * [ F(n-2) ]

Expanding this provides two equations:
	F(n)   = a * F(n-1) + b * F(n-2)
	F(n-1) = c * F(n-1) + d * F(n-2)

By comparing with the Fibonacci recurrence:
	F(n)   = F(n-1) + F(n-2)
	F(n-1) = F(n-1)

The coefficients are found as: a = 1, b = 1, c = 1, d = 0

Thus, the matrix A is:
A = [ 1  1 ]
	[ 1  0 ]

This matrix expresses the Fibonacci recurrence in matrix form, allowing for efficient computation using matrix exponentiation.
*/
int fibonacci(int n) {
	if (n < 1) return 0;

	if (n == 1 || n == 2) return 1;

	vector<vector<int>> baseMatrix = { {1,1},{1,0} };

	vector<vector<int>> resultMatrix =
		matrixExponentiation(baseMatrix, n - 2);

	//F(1) = 1, F(2) = 1
	//F(n) = a*F(2) + b*F(1) = a*1 + b*1
	return resultMatrix[0][0] + resultMatrix[1][0];
}


/*
Cows Reproduction
In the first year, there is one mature cow (Cow A) on the farm. Each year, the following occurs:

1. Each mature cow gives birth to one cow every year.
2. Every newborn cow matures and starts giving birth in its third year.
3. No cow ever dies.

Return the total number of cows on the farm after N years.


Matrix A is derived from the recurrence relation: f(n) = f(n-1) + f(n-3)

This recurrence relation is represented in matrix form using the state vector V(n):
V(n) = [ f(n), f(n-1), f(n-2) ]^T

Matrix A is constructed as follows:
1. f(n) = 1 * f(n-1) + 0 * f(n-2) + 1 * f(n-3)
2. f(n-1) = 1 * f(n-1) + 0 * f(n-2) + 0 * f(n-3)
3. f(n-2) = 0 * f(n-1) + 1 * f(n-2) + 0 * f(n-3)

Thus, the base matrix A is:
A = [ 1  0  1 ]
	[ 1  0  0 ]
	[ 0  1  0 ]

Matrix A is used for calculating the future population of cows via matrix exponentiation.
*/
int cowPopulation(int n) {
	if (n < 1) return 0;

	if (n <= 3) return n;

	vector<vector<int>> baseMatrix = {
		{1,0,1},
		{1,0,0},
		{0,1,0}
	};
	vector<vector<int>> resultMatrix = matrixExponentiation(baseMatrix, n - 3);

	int cowCount = 0;
	vector<int> initialState = { 3,2,1 };
	for (int i = 0; i < 3; i++)
		cowCount += resultMatrix[0][i] * initialState[i];

	return cowCount;
}