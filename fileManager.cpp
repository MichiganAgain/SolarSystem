#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "fileManager.hpp"

std::string FileManager::readFile(std::string fileName) {
    std::stringstream stringStream;
    std::ifstream file{fileName, std::ios::in};
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << fileName << std::endl;
        throw std::runtime_error("Failed to open file");
    }
    stringStream << file.rdbuf();

    return stringStream.str();
}
