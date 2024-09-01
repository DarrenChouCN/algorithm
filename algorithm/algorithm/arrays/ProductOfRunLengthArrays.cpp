/*
Run-length encoding is a compression algorithm that allows for an integer array nums with many segments of consecutive repeated numbers to be represented by a (generally smaller) 2D array encoded. Each encoded[i] = [vali, freqi] describes the ith segment of repeated numbers in nums where vali is the value that is repeated freqi times.
Note: Compression should be done such that the run-length encoded array has the minimum possible length.

For example:
1. Input: encoded1 = [[1, 3], [2, 2]] £¨nums1 = [1, 1, 1, 2, 2], encoded2 = [[2, 3], [3, 2]] £¨nums2 = [2, 2, 2, 3, 3]£©
2. Expand: nums1 = [1, 1, 1, 2, 2], nums2 = [2, 2, 2, 3, 3]
3. Multiply : proNums = [1*2, 1*2, 1*2, 2*3, 2*3] = [2, 2, 2, 6, 6]
4. Encode: proNums = [[2, 3], [6, 2]]

1. Two pointers i and j are initialized to traverse encoded1 and encoded2. Two auxiliary variables remainingFreq1 and remainingFreq2 track the unprocessed frequencies of the current segments.
2. For each pair of segments from encoded1 and encoded2, the minimum of the remaining frequencies (minFreq) is determined. The product of the current values from the two segments is calculated. If the product matches the last segment in the result, merge them by increasing the frequency. Otherwise, a new segment is added to the result.
3. The remaining frequencies are updated by subtracting minFreq. If a segment is fully processed (remainingFreq1 or remainingFreq2 becomes zero), the corresponding pointer (i or j) moves to the next segment.
4. The final run-length encoded array representing the element-wise product is returned.

Optimized Solution:
1. The algorithm avoids redundant multiplications by processing the minimal frequency between corresponding segments from the two encoded arrays at each step. This ensures each multiplication is performed only when necessary.
2. To avoid modifying the input arrays, two auxiliary integer variables remainingFreq1 and remainingFreq2 are used to track the unprocessed portion of the current segment in each array. This approach allows efficient traversal and processing of the segments without altering the original data.
3. The algorithm merges consecutive segments with the same product value to maintain the compressed nature of the run-length encoding, thus minimizing the output array size.

Time Complexity: O(m+n)
Space Complexity: O(1)
*/

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> findRLEArray(const vector<vector<int>>& encoded1, const vector<vector<int>>& encoded2) {

    vector<vector<int>> result;
    int i = 0, j = 0;
    int remainingFreq1 = 0, remainingFreq2 = 0;

    while (i < encoded1.size() && j < encoded2.size()) {

        if (remainingFreq1 == 0) 
            remainingFreq1 = encoded1[i][1];

        if (remainingFreq2 == 0) 
            remainingFreq2 = encoded2[j][1];

        int minFreq = min(remainingFreq1, remainingFreq2);
        int product = encoded1[i][0] * encoded2[j][0];

        if (!result.empty() && result.back()[0] == product) {
            result.back()[1] += minFreq;
        }
        else {
            result.push_back({ product, minFreq });
        }

        remainingFreq1 -= minFreq;
        remainingFreq2 -= minFreq;

        if (remainingFreq1 == 0) 
            i++;
        if (remainingFreq2 == 0) 
            j++;
    }

    return result;
}

int mainFindRLEArray() {
	vector<vector<int>> encoded1 = { {1, 3}, {2, 3} };
	vector<vector<int>> encoded2 = { {6, 3}, {3, 3} };

	vector<vector<int>> result = findRLEArray(encoded1, encoded2);

	for (const auto& pair : result) {
		cout << "[" << pair[0] << ", " << pair[1] << "] ";
	}
	cout << endl;

	return 0;
}

