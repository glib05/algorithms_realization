#include "internal_sort.h"
#include <fstream>
#include "merge_sort.h"

using namespace std;

void internalSort(const string& name_a, const string& name_b, const int& step){
    fstream file_a(name_a, ios::in|ios::binary);
    if (!file_a)
        throw fstream::failure("Файл "+name_a+" не відкрився internal");
    createFile(name_b);
    fstream file_b(name_b, ios::out|ios::binary);
    if (!file_b)
        throw fstream::failure("Файл "+name_b+" не відкрився internal");

    file_a.seekg(0, std::ios::beg);

    bool exit = false;
    int i, num;
    int* arr = new int[step];
    while (!exit){
        for (i = 0; i<step; i++){
            if (file_a.read(reinterpret_cast<char*>(&num), sizeof(num))){
                arr[i] = num;
            }
            else{
                exit = true;
                break;
            }
        }
        mergeSort(arr,0, i-1);
        for (int j = 0; j<i; j++)
            file_b.write(reinterpret_cast<char*>(&arr[j]), sizeof(arr[j]));
    }

    delete[] arr;

    file_a.close();
    file_b.close();

    file_a.open(name_a, ios::out|ios::binary);
    if (!file_a)
        throw fstream::failure("Файл "+name_a+" не відкрився internal");
    file_b.open(name_b, ios::in|ios::binary);
    if (!file_b)
        throw fstream::failure("Файл "+name_b+" не відкрився internal");

    file_a << file_b.rdbuf();

    file_a.close();
    file_b.close();
}