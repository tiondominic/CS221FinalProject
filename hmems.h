#ifndef HMEMS_H
#define HMEMS_H

#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <iomanip>

using namespace std;

// Binary search function for early termination during merging
int binarySearch(const vector<int>& arr, int left, int right);

// Insertion Sort with Binary Search Optimization for small segments
void binaryInsertionSort(vector<int>& arr, int left, int right);

// Merge function with adaptive merging strategy
void hmems_merge(vector<int>& A, int L1, int R1, int L2, int R2);

// Main function for the adaptive merge sort
void hmems(vector<int>& A);

#endif