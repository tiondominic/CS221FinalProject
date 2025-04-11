#include <iostream>
#include <vector>
#include "mems.h"


/*
TODO 
- Add Binary Search for early termination | High Priority
- Add Parallel computing for the merge steps | Medium Priority
- Finish the merge sort function *Done*
- Add a file reading system to calculate data | Low Priority
- Add output file as txt after finish sorting | Medium Priority
- Add timer to benchmark code | Low Priority
- Move main.cpp into a header file |
- create a new main.cpp file to handle the gui to pick 
which data to use in testdata/file.txt file and which algorithm to use |
- think more modularity
- add feature to modify/create new file for sorted data
- MODIFIED ENHANCED MERGESORT - MEMS
*/


std::vector<int> mems_merge(std::vector<int> Left, std::vector<int> Right) {
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

std::vector<int> mems(std::vector<int>& arr) {
    int size = arr.size();
    if(size <= 1) {
        return arr;
    }
    int mid = size / 2;
    std::vector<int> leftHalf(arr.begin(), arr.begin() + mid);
    std::vector<int> rightHalf(arr.begin() + mid, arr.end());
    
    leftHalf = mems(leftHalf);
    rightHalf = mems(rightHalf);
    return mems_merge(leftHalf, rightHalf);
}

// int main() {
//     vector<int> Numbers = read_file();  // Read the file
//     clock_t start = clock();
//     mergesort(Numbers);
//     clock_t end = clock();

//     double time_taken = double(end - start) / CLOCKS_PER_SEC;
//     cout << "Using Modified EMS time taken: " << time_taken << endl;
//     cout << "Press Enter to exit..." << std::endl;
//     cin.get(); 
//     return 0;
// }