#include "file_functions.h"
#include <fstream>
#include <iomanip>

using namespace std;

void createFile(const string &filename){
    ofstream file(filename, ios::binary);
    if(!file){
        throw fstream::failure("Файл "+filename+" не створився");
    }
    else
        file.close();
}

void printFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    if (!file)
        throw std::fstream::failure("Файл " + filename + " не відкрився print");

    int num;

    while (file.read(reinterpret_cast<char *>(&num), sizeof(num))) {
        std::cout << std::setw(7);
        std::cout << num << " ";
    }

    file.close();
}

void createFileWithRandomNumbers(const string& filename, const unsigned int& size){
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distribution(-100000, 100000);

    int r;
    ofstream file(filename, ios::binary);
    for (long long i = 0; i<size; i++){
        r = distribution(gen);
        file.write(reinterpret_cast<const char *>(&r), sizeof(r));
    }
    file.close();
}