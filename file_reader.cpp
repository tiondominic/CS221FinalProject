#include "file_reader.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;


vector<int> read_file(const fs::path& filename){
    std::ifstream file(filename);
    std::vector<int> data;

    if (!file) {
        std::cerr << "Error: "<< filename << "does not exist" << std::endl;
        return data;
    }

    int num;
    while (file >> num) {
        data.push_back(num);
    }

    file.close();
    return data;
}
