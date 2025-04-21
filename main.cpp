#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <ctime>
#include <fstream>
#include <filesystem>

#include "file_reader.h"
#include "mems.h"
#include "memsB.h"
#include "EMSOriginal.h"

namespace fs = std::filesystem;

void writeToFile(const std::vector<int>& arr, const std::string& algorithmName) {
    std::filesystem::create_directory("output"); 
    
    std::stringstream filename;
    filename << "output/" << algorithmName << "_sorted.txt";
    
    std::ofstream outFile(filename.str());  
    
    if (outFile.is_open()) {
        for (const int& num : arr) {
            outFile << num << "\n";
        }
        outFile << std::endl;
        outFile.close();
        std::cout << "Sorted array has been written to " << filename.str() << std::endl;
    } else {
        std::cout << "Error opening file for writing!" << std::endl;
    }
}


void sortVector(std::vector<int>& arr, int choice) {
    std::vector<int> sortedArr;

    switch(choice) {
        case 1:
            sortedArr = mems(arr); 
            writeToFile(sortedArr, "mems");
            break;
        case 2:  
            sortedArr = memsB(arr);
            writeToFile(sortedArr, "memsB");
            break;
        case 3:  
            enhancedMergeSort(arr);
            writeToFile(arr, "enhancedMergeSort");
            break;
        case 4:
            std::cout << "Exiting...";
            exit(0);
            break;
        default:
            std::cout << "Invalid choice!" << std::endl;
            return;
    }
}


int main(){
    std::string path = "testdata";
    std::vector<fs::path> options;
    int i=0;
    int sortChoice;

    if (!fs::exists(path)) {
        fs::create_directory(path);
    }

    std::cout << "1. MEMS\n2. MEMSB\n3. EMS\n4. Exit\nSelect: ";
    std::cin >> sortChoice;
    system("cls");

    
    for(const auto& entry: fs::directory_iterator(path)){

        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            options.push_back(entry.path());
            std::cout << ++i << ": " << entry.path().string() << std::endl;
        }
    }

    
    size_t choice;
    std::cout << "Select: ";
    std::cin >> choice;
    system("cls");

    std::vector<int> arr = read_file(options[choice-1]);
    std::cout << "Sorting...";
    auto start = std::chrono::high_resolution_clock::now();
    
    sortVector(arr, sortChoice);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double>(end - start).count();

    system("cls");

    std::cout << "time taken: " << duration << endl;
    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.ignore();
    std::cin.get(); 
    return 0;
}

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
