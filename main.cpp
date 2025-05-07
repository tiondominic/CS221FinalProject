#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <ctime>
#include <sstream>
#include <filesystem>

#include "file_reader.h"
#include "mems.h"
#include "memsB.h"
#include "hmems.h"
#include "EMSOriginal.h"

namespace fs = std::filesystem;

void writeToFile(const std::vector<int>& arr, const std::string& algorithmName, int times) {
    std::filesystem::create_directory("output"); 
    
    std::stringstream filename;
    filename << "output/" << algorithmName << times << "_sorted.txt";
    
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


void sortVector(std::vector<int> arr, int choice, int times) {
    std::vector<int> sortedArr;

    switch(choice) {
        case 1:
            mems(arr); 
            writeToFile(arr, "mems", times);
            break;
        case 2:  
            sortedArr = memsB(arr);
            writeToFile(sortedArr, "memsB", times);
            break;
        case 3:  
            enhancedMergeSort(arr);
            writeToFile(arr, "enhancedMergeSort", times);
            break;
        case 4:  
            hmems(arr);
            writeToFile(arr, "hmems", times);
            break;
    }
}

void sorting(int number){
    int i=0;
    std::vector<fs::path> options;
    std::string path = "testdata";

    if (!fs::exists(path)) {
        fs::create_directory(path);
    }

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

    int times;

    std::cout << "Repeat amount: ";
    std::cin >> times;

    std::cout << "Opening file...";
    std::vector<int> arr = read_file(options[choice-1]);

    system("cls");
    std::cout << "Sorting...";

    for(int i=1; i <= times; i++){
        auto start = std::chrono::high_resolution_clock::now();
        
        sortVector(arr, number, i);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double>(end - start).count();

        std::cout << "Sort #" << i << " : " << duration << endl;
    }

    std::cout << "Press Enter to retry..." << std::endl;
    std::cin.ignore();
    std::cin.get(); 

    system("cls");
}

int main(){
    while(true){
        int sortChoice;

        std::cout << "1. MEMS\n2. MEMSB\n3. EMS\n4. HMEMS\n5. Exit\nSelect: ";
        std::cin >> sortChoice;
        system("cls");

        switch(sortChoice){
            case 1:
            case 2:
            case 3:
            case 4:
                sorting(sortChoice);
                break;
            case 5:
                std::cout << "Exiting...";
                exit(0);
            default:
                std::cout << "Invalid choice";
                system("cls");

        }
    
    }
    return 0;
}

/*
TODO 
All done
*/
