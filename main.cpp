#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <ctime>

#include "file_reader.h"
#include "mems.h"

namespace fs = std::filesystem;

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
*/


int main(){
    std::string path = "testdata";
    std::vector<fs::path> options;
    int i=0;
    int sortChoice;

    std::cout << "1. MEMS\n2. EMS\nSelect: ";
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
    clock_t start = clock();
    std::cout << "Sorting...";
    mems(arr);
    clock_t end = clock();

    system("cls");
    
    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Using MEMS time taken: " << time_taken << endl;
    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.ignore();
    std::cin.get(); 
    return 0;
}