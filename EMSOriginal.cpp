#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <iomanip>

#include "file_reader.h"
using namespace std;

void merge(vector<int>& A, int L1, int R1, int L2, int R2) {
    vector<int> temp(A.begin() + L1, A.begin() + R2 + 1);
    int i = 0, j = R1 - L1 + 1, k = L1;

    while (i <= R1 - L1 && j <= R2 - L1) {
        if (temp[i] <= temp[j]) {
            A[k++] = temp[i++];
        } else {
            A[k++] = temp[j++];
        }
    }

    while (i <= R1 - L1) A[k++] = temp[i++];
    while (j <= R2 - L1) A[k++] = temp[j++];
}

void enhancedMergeSort(vector<int>& A) {
    int n = A.size();

    for (int i = 0; i < n - 1; i += 2) {
        if (A[i] > A[i + 1]) {
            swap(A[i], A[i + 1]);
        }
    }

    for (int size = 2; size < n; size *= 2) {
        for (int left = 0; left + size < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = min(left + 2 * size - 1, n - 1);


            if (A[mid] <= A[mid + 1]) {
                continue;
            }

            if (A[right] <= A[left]) {
                for (int i = 0; i < size && mid + 1 + i <= right; ++i) {
                    swap(A[left + i], A[mid + 1 + i]);
                }
                continue;
            }

            // Case C
            merge(A, left, mid, mid + 1, right);
        }
    }
}
