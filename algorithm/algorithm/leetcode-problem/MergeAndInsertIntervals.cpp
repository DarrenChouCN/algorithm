#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

/*
Insert Intervals

You are given an array of non-overlapping intervals intervals where intervals[i] = [starti, endi] represent the start and the end of the ith interval and intervals is sorted in ascending order by starti. You are also given an interval newInterval = [start, end] that represents the start and end of another interval.
Insert newInterval into intervals such that intervals is still sorted in ascending order by starti and intervals still does not have any overlapping intervals (merge overlapping intervals if necessary).
Return intervals after the insertion.

1. If the current interval's end is less than 'newInterval''s start point, it means the current interval is before 'newInterval' and does not overlap. Add it directly to the result list.
2. If the current interval's start is less than 'newInterval''s end point, it means the current interval overlaps with 'newInterval'. Merge it by updating 'newInterval''s start and end points to encompass the overlappint interval.
3. If the current interval's start point is greater than 'newInterval''s end point, it means the current interval is after 'newInterval' and does not overlap. Add it directly to the result list.

Time Complexity: O(n)
Space Complexity: O(n)
*/
vector<vector<int>> insertInterval(vector<vector<int>>& intervals, vector<int>& newInterval) {
	vector<vector<int>> result;
	int i = 0;
	int n = intervals.size();

	while (i < n && intervals[i][1] < newInterval[0])
	{
		result.push_back(intervals[i++]);
	}

	while (i < n && intervals[i][0] <= newInterval[1])
	{
		newInterval[0] = min(newInterval[0], intervals[i][0]);
		newInterval[1] = max(newInterval[1], intervals[i][1]);
		i++;
	}
	result.push_back(newInterval);

	while (i < n)
	{
		result.push_back(intervals[i++]);
	}
	return result;
}

int mainInsertInterval() {
	vector<vector<int>> intervals1 = { {1, 3}, {6, 9} };
	vector<int> newInterval1 = { 2, 5 };
	vector<vector<int>> result1 = insertInterval(intervals1, newInterval1);
	cout << "Merged intervals: ";
	for (const auto& interval : result1) {
		cout << "[" << interval[0] << "," << interval[1] << "] ";
	}
	cout << endl;

	vector<vector<int>> intervals2 = { {1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16} };
	vector<int> newInterval2 = { 4, 8 };
	vector<vector<int>> result2 = insertInterval(intervals2, newInterval2);
	cout << "Merged intervals: ";
	for (const auto& interval : result2) {
		cout << "[" << interval[0] << "," << interval[1] << "] ";
	}
	cout << endl;

	return 0;
}



/*
Merge Intervals

Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.

1. Sort the intervals based on their starting points in ascending order.
2. Create a new array to store the merged intervals.
3. Compare each interval with the last interval in the result array.
	If the current interval's starting point is less than or equal to the ending point of the last interval in the result array, merge them.
	If the current interval's starting point is greater than the ending point of the last interval in the result array, add the current interval to the result array as a separate interval.


Time Complexity: O(nlogn)
Space Complexity: O(n)
*/
vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {
	if (intervals.empty())
	{
		return {};
	}

	sort(intervals.begin(), intervals.end());
	vector<vector<int>> merged;
	merged.push_back(intervals[0]);

	for (int i = 0; i < intervals.size(); i++)
	{
		auto& last = merged.back();
		if (intervals[i][0] <= last[1])
		{
			last[1] = max(last[1], intervals[i][1]);
		}
		else {
			merged.push_back(intervals[i]);
		}
	}

	return merged;
}

int mainMergeIntervals() {
	vector<vector<int>> intervals1 = { {1, 3}, {2, 6}, {8, 10}, {15, 18} };
	vector<vector<int>> result1 = mergeIntervals(intervals1);
	cout << "Merged intervals: ";
	for (const auto& interval : result1) {
		cout << "[" << interval[0] << "," << interval[1] << "] ";
	}
	cout << endl;

	vector<vector<int>> intervals2 = { {1, 4}, {4, 5} };
	vector<vector<int>> result2 = mergeIntervals(intervals2);
	cout << "Merged intervals: ";
	for (const auto& interval : result2) {
		cout << "[" << interval[0] << "," << interval[1] << "] ";
	}
	cout << endl;

	return 0;
}