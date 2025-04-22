#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <thread>

#include "mems.h"
using namespace std;

void mems_merge(vector<int>& A, int L1, int R1, int L2, int R2) {
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

const int THREAD_THRESHOLD = 10000;

void mems(std::vector<int>& A) {
    int n = A.size();
    unsigned int max_threads = std::thread::hardware_concurrency();
    if (max_threads == 0) max_threads = 4;

    for (int i = 0; i < n - 1; i += 2) {
        if (A[i] > A[i + 1]) {
            std::swap(A[i], A[i + 1]);
        }
    }

    for (int size = 2; size < n; size *= 2) {
        std::vector<std::thread> threads;

        for (int left = 0; left + size < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = std::min(left + 2 * size - 1, n - 1);
            int range_size = right - left + 1;

            if (range_size >= THREAD_THRESHOLD && threads.size() < max_threads) {
                threads.emplace_back([&, left, mid, right]() {
                    if (A[mid] <= A[mid + 1]) return;

                    if (A[right] <= A[left]) {
                        for (int i = 0; i < size && mid + 1 + i <= right; ++i) {
                            std::swap(A[left + i], A[mid + 1 + i]);
                        }
                        return;
                    }

                    mems_merge(A, left, mid, mid + 1, right);
                });
            } else {
                // Main thread
                if (A[mid] <= A[mid + 1]) continue;

                if (A[right] <= A[left]) {
                    for (int i = 0; i < size && mid + 1 + i <= right; ++i) {
                        std::swap(A[left + i], A[mid + 1 + i]);
                    }
                    continue;
                }

                mems_merge(A, left, mid, mid + 1, right);
            }
        }

        for (auto& t : threads) {
            if (t.joinable()) t.join();
        }
    }
}
