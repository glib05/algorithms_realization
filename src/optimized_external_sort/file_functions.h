#ifndef PRO_ALG_1_MERGE_FILE_FUNCTIONS_H
#define PRO_ALG_1_MERGE_FILE_FUNCTIONS_H

#include <iostream>
#include <chrono>
#include <random>

void createFileWithRandomNumbers(const std::string& filename, const unsigned int& size);
void createFile(const std::string &filename);
void printFile(const std::string &filename);

#endif