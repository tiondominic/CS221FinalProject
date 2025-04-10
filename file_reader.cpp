#include "file_reader.h"

#include <iostream>
#include <fstream>
#include <vector>


std::vector<int> read_file() {
    std::ifstream file("testdata/data_50000.txt"); //this is temporary (need to make it so that it can choose any file from the folder)
    std::vector<int> data;

    if (!file) {
        std::cerr << "Error: testdata/data_50000.txt missing or could not be opened!" << std::endl;
        return data;
    }

    int num;
    while (file >> num) {
        data.push_back(num);
    }

    file.close();
    return data;
}
