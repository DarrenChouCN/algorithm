#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;
/*
Reservoir Sampling Problem
You are given a stream of unknown length from which elements are continuously emitted. You have a reservoir (a collection) that can hold k elements. Each new element from the stream can either be added to the reservoir or discarded forever.
Design an algorithm that ensures every element in the stream has an equal probability of being included in the reservoir after the stream ends.

Example:
If k = 1, then at the end of the stream, each element should have a 1/n probability of being in the reservoir, where n is the total number of elements in the stream.
If k = 10, then each element in the stream should have a 10/n probability of being included in the reservoir.
Constraints:
You do not know the length of the stream in advance.
You can only use O(k) additional space.
Goal: Implement an efficient algorithm to maintain a random sample of k elements from a stream of unknown length.

In reservoir sampling, j is used to manage the index within the reservoir. For each element at index i in the data stream, a random index j is generated within the range [0, i]. If j falls within [0, k-1], then the element at index i in the stream replaces the element at index j in the reservoir. This mechanism simulates the probability k/i for each element to be included in the reservoir.

Time and Space Complexity: O(n) and O(k)
*/
vector<int> reservoirSampling(const vector<int>& stream, int k) {
	int n = stream.size();
	vector<int> reservoir(k);

	// Fill the reservoir with the first k elements
	for (int i = 0; i < k; i++)
		reservoir[i] = stream[i];

	for (int i = k; i < n; i++)
	{
		// Generate a random index j between 0 and i
		int j = rand() % (i + 1);

		// With probability k/i, replace an element in the reservoir
		if (j < k)
			reservoir[j] = stream[i];
	}

	return reservoir;
}

int main() {
	srand(time(0));  // Set the random seed

	// Simulated data stream
	vector<int> stream = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	int k = 10;  // Reservoir size

	// Execute reservoir sampling
	vector<int> result = reservoirSampling(stream, k);

	cout << "Reservoir sampling result:" << endl;
	for (int num : result) {
		cout << num << " ";
	}
	cout << endl;

	return 0;
}
