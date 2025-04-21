#include <iostream>
#include <vector>
#include <thread>

#include "memsB.h"
const int THREAD_THRESHOLD = 10000;

std::vector<int> memsB_merge(std::vector<int> Left, std::vector<int> Right) {
    std::vector<int> result;
    int sizeL = Left.size();
    int sizeR = Right.size();
    int i = 0, j = 0;

    while(i < sizeL && j < sizeR) {
        if (Left[i] <= Right[j])
            result.push_back(Left[i++]);
        else
            result.push_back(Right[j++]);
    }

    while (i < sizeL)
        result.push_back(Left[i++]);
    while (j < sizeR)
        result.push_back(Right[j++]);

    return result;
}

std::vector<int> memsB(std::vector<int>& arr) {
    int size = arr.size();
    if(size <= 1) {
        return arr;
    }

    int mid = size / 2;
    std::vector<int> leftHalf(arr.begin(), arr.begin() + mid);
    std::vector<int> rightHalf(arr.begin() + mid, arr.end());

    std::vector<int> sortedLeft, sortedRight;

    if (size >= THREAD_THRESHOLD) {
        std::thread leftThread([&]() {
            sortedLeft = memsB(leftHalf);
        });

        std::thread rightThread([&]() {
            sortedRight = memsB(rightHalf);
        });

        leftThread.join();
        rightThread.join();
    } else {
        sortedLeft = memsB(leftHalf);
        sortedRight = memsB(rightHalf);
    }

    return memsB_merge(sortedLeft, sortedRight);
}