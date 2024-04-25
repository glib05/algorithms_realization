#ifndef PRO_ALG_1_MERGE_EXTERNAL_SORT_H
#define PRO_ALG_1_MERGE_EXTERNAL_SORT_H

#include <iostream>
#include "internal_sort.h"


using namespace std;

const double RAM = 0.5;

class ExternalSimpleFileSort{
public:
    explicit ExternalSimpleFileSort(const string& filename);
    ~ExternalSimpleFileSort();
private:
    string mFileName;
    string mFileBName = "B.bin";
    string mFileCName = "C.bin";

    void sort();
    void splitFile(const int& step);
    void mergeFiles(const int& step);
};

#endif
