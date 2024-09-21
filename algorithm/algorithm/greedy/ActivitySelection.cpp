#include <iostream>
#include <vector>
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