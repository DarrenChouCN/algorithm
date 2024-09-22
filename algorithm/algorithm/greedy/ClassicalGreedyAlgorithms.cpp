#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

/*
Activity Selection Problem
Given an array of projects where each project has a start and end time, schedule the projects in such a way that the maximum number of non-overlapping projects can be attended in a meeting room. The strategy involves sorting the projects based on their end times. For each project, if it starts after the previous one ends, it can be included; otherwise, it should be skipped.

Strategies: Sorting by end time, start time, duration.
Expected Results: Generally, sorting by end time will produce the maximum number of non-overlapping projects, confirming that it is the optimal greedy strategy for this problem.

Time and Space Complexity: O(nlogn) and O(n)
*/

struct Project
{
	int start;
	int end;
};

// Comparator for sorting by duration
bool compareByDuration(const Project& a, const Project& b) {
	return (a.end - a.start) < (b.end - b.start);
}

// Comparator for sorting by start time
bool compareByStart(const Project& a, const Project& b) {
	return a.start < b.start;
}

// Comparator for sorting by end time
bool compareByEnd(const Project& a, const Project& b) {
	// Comparator for sorting by duration
	//return (a.end - a.start) < (b.end - b.start);

	// Comparator for sorting by start time
	//return a.start < b.start;

	return a.end < b.end;
}

int maxEvents(vector<Project>& projects, bool (*compare)(const Project&, const Project&)) {
	// Sort projects by end time using the comparator
	sort(projects.begin(), projects.end(), compare);

	int count = 0, lastEndTime = 0;
	for (const auto& project : projects)
	{
		if (project.start >= lastEndTime) {
			count++;
			lastEndTime = project.end;
		}
	}
	return count;
}

vector<Project> generateRandomProjects(int n) {
	vector<Project> projects;
	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		int start = rand() % 100;
		int end = start + (rand() % 20 + 1);
		projects.push_back({ start,end });
	}
	return projects;
}

int mainMaxEvents() {
	int sampleSize = 10000;  // Number of random projects to generate
	vector<Project> projects = generateRandomProjects(sampleSize);

	// Apply the optimal greedy strategy and get the result
	int countByEnd = maxEvents(projects, compareByEnd);
	int countByStart = maxEvents(projects, compareByStart);
	int countByDuration = maxEvents(projects, compareByDuration);

	cout << "Max projects by end time: " << countByEnd << endl;
	cout << "Max projects by start time: " << countByStart << endl;
	cout << "Max projects by duration: " << countByDuration << endl;

	return 0;
}

/*
Gold Bar Cutting Problem
You have a gold bar of length n, and you want to divide it into smaller pieces. Each time you cut the gold bar, the cost is equal to the length of the gold bar you are cutting. The goal is to split the gold bar into multiple pieces in such a way that the total cost of all the cuts is minimized.

Huffman-like Greedy Algorithm
To minimize the total cost of cutting the gold bar, the strategy is to always combine the two smallest pieces of gold at each step. This ensures that the larger pieces are cut later, reducing the overall cost.

Time and Space Complexity: O(nlogn) and O(n)
*/
int minCostToCutGoldBar(const vector<int>& lengths) {
	priority_queue<int, vector<int>, greater<int>> minHeap(lengths.begin(), lengths.end());

	int totalCost = 0;

	while (minHeap.size() > 1) {
		int first = minHeap.top();
		minHeap.pop();
		int second = minHeap.top();
		minHeap.pop();

		int cost = first + second;
		totalCost += cost;

		minHeap.push(cost);
	}

	return totalCost;
}

/*
Profit Maximization
You are given a set of projects, each with an associated cost and profit. The goal is to maximize your total amount of money by selecting up to k projects. You start with an initial capital m, and each time you select a project, you can only choose one that you can afford with your current capital. The aim is to complete at most k projects and achieve the maximum final capital.

Greedy with Priority Queues
A min-heap to manage projects by their cost and a max-heap to select the project with the highest profit among the projects.
The maximum profit is inserted into the max-heap. Projects are initially added to a min-heap, prioritized by their cost in ascending order. A loop runs with the maximum limit being the number of projects that can be selected. In each iteration, the top element of the min-heap is checked to see if its cost is less than or equal to the current available capital. If the condition is met, the project is moved from the min-heap (smallest cost) to the max-heap (maximum profit). Then, the top element of the max-heap (maximum profit) is added to the current capital, and it is removed from the heap. This process repeats until no more valid projects can be selected.

Time and Space Complexity: O(nlogn) and O(n)
*/
int maximizeCapital(int k, int initialCapital, vector<int>& costs, vector<int>& profits) {
	priority_queue<pair<int, int>, vector<pair<int, int>>,
		greater<pair<int, int>>> minCostHeap;

	priority_queue<int> maxProfitHeap;

	for (int i = 0; i < costs.size(); i++)
		minCostHeap.push({ costs[i],profits[i] });

	int currentCapital = initialCapital;

	for (int i = 0; i < k; i++)
	{
		while (!minCostHeap.empty() && minCostHeap.top().first <= currentCapital) {
			maxProfitHeap.push(minCostHeap.top().second);
			minCostHeap.pop();
		}

		if (maxProfitHeap.empty()) break;

		currentCapital += maxProfitHeap.top();
		maxProfitHeap.pop();
	}
	return currentCapital;
}