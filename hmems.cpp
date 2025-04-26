#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include <algorithm>

#include "hmems.h"
using namespace std;

// Binary search to find where to insert value in a sorted array
int binarySearch(const vector<int>& A, int left, int right, int key) {
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (A[mid] < key) left = mid + 1;
        else right = mid;
    }
    return left;
}

// Hybrid insertion + binary search sort for small arrays
void binaryInsertionSort(vector<int>& A, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int key = A[i];
        int pos = binarySearch(A, left, i, key);
        for (int j = i; j > pos; --j) {
            A[j] = A[j - 1];
        }
        A[pos] = key;
    }
}

// Merging two sorted subarrays A[L1..R1] and A[L2..R2]
void hmems_merge(vector<int>& A, int L1, int R1, int L2, int R2) {
    int i = L1, j = L2;
    vector<int> temp;
    
    while (i <= R1 && j <= R2) {
        if (A[i] <= A[j]) {
            temp.push_back(A[i]);
            i++;
        } else {
            temp.push_back(A[j]);
            j++;
        }
    }
    
    while (i <= R1) {
        temp.push_back(A[i]);
        i++;
    }
    
    while (j <= R2) {
        temp.push_back(A[j]);
        j++;
    }
    
    for (int k = 0; k < temp.size(); ++k) {
        A[L1 + k] = temp[k];
    }
}

// Sort function with hybrid sorting and parallel merging
const int INSERTION_SORT_THRESHOLD = 32;

void hmems(vector<int>& A) {
    int n = A.size();
    unsigned int max_threads = thread::hardware_concurrency();
    if (max_threads == 0) max_threads = 4;

    // Step 1: Sort small chunks first using hybrid insertion sort
    for (int i = 0; i < n; i += INSERTION_SORT_THRESHOLD) {
        binaryInsertionSort(A, i, min(i + INSERTION_SORT_THRESHOLD - 1, n - 1));
    }

    // Step 2: Merge chunks, doubling size each time
    for (int size = INSERTION_SORT_THRESHOLD; size < n; size *= 2) {
        vector<thread> threads;

        for (int left = 0; left < n - size; left += 2 * size) {
            int mid = left + size - 1;
            int right = min(left + 2 * size - 1, n - 1);

            // Parallel merge if large enough
            if (right - left >= 100000 && threads.size() < max_threads) {
                threads.emplace_back([&, left, mid, right]() {
                    hmems_merge(A, left, mid, mid + 1, right);
                });
            } else {
                hmems_merge(A, left, mid, mid + 1, right);
            }
        }

        for (auto& t : threads) {
            if (t.joinable()) t.join();
        }
    }
}