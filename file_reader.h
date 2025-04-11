#ifndef FILE_READER_H
#define FILE_READER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

vector<int> read_file(const fs::path& filename);



#endif
