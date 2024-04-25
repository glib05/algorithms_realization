#include "external_sort.h"
#include <fstream>

using namespace std;

ExternalSimpleFileSort::ExternalSimpleFileSort(const string &filename) {
    mFileName = filename;
    sort();
}


ExternalSimpleFileSort::~ExternalSimpleFileSort() {
    remove(mFileBName.c_str());
    remove(mFileCName.c_str());
}

void ExternalSimpleFileSort::sort() {

    createFile(mFileBName);
    createFile(mFileCName);

    ifstream file_a(mFileName, ios::in | ios::binary);
    if (!file_a)
        throw fstream::failure("Файл " + mFileName + " не відкрився 1");
    file_a.seekg(0, std::ios::end);
    unsigned int size_a = file_a.tellg()/sizeof(int);

    file_a.close();

    unsigned int size_a_extendable = size_a;

    while ((size_a_extendable & size_a_extendable - 1))
        size_a_extendable++;

    double ramm = (RAM * 1024 * 1024 * 1024) / sizeof(int) * 0.15;
    int j = 1;
    while (j < ramm and j <= size_a)
        j*=2;
    j/=2;
    internalSort(mFileName, mFileBName, j);

    for (int i = j; i <= size_a_extendable / 2; i*=2) {
        splitFile( i);
        mergeFiles(i);
    }

    file_a.open(mFileName, ios::in | ios::binary);
    if (!file_a)
        throw fstream::failure("Файл " + mFileName + " не відкрився 1");
    file_a.seekg(0, std::ios::end);
    unsigned int size_a_after_sort = file_a.tellg()/sizeof(int);
    file_a.close();

    if (size_a != size_a_after_sort)
        throw fstream::failure("Розмір файлу змінився");
}

void ExternalSimpleFileSort::splitFile(const int &step) {
    ifstream file_a(mFileName, ios::in | ios::binary);
    if (!file_a)
        throw fstream::failure("Файл " + mFileName + " не відкрився split");
    ofstream file_b(mFileBName, ios::binary);
    if (!file_b)
        throw fstream::failure("Файл "+mFileBName+" не відкрився split");
    ofstream file_c(mFileCName, ios::binary);
    if (!file_c)
        throw fstream::failure("Файл "+mFileCName+" не відкрився split");

    int num;

    bool exit = false;

    while (!exit){
        for (int i = 0; i<step; i++)
            if (file_a.read(reinterpret_cast<char *>(&num), sizeof(num)))
                file_b.write(reinterpret_cast<char *>(&num), sizeof(num));
            else
                exit = true;

        for (int i = 0; i<step; i++)
            if (file_a.read(reinterpret_cast<char *>(&num), sizeof(num)))
                file_c.write(reinterpret_cast<char *>(&num), sizeof(num));
            else
                exit = true;
    }

    file_a.close();
    file_b.close();
    file_c.close();
}

void ExternalSimpleFileSort::mergeFiles(const int &step) {
    ofstream file_a(mFileName, ios::binary);
    if (!file_a)
        throw fstream::failure("Файл " + mFileName + " не відкрився merge");
    ifstream file_b(mFileBName, ios::in|ios::binary);
    if (!file_b)
        throw fstream::failure("Файл "+mFileBName+" не відкрився merge");
    ifstream file_c(mFileCName, ios::in|ios::binary);
    if (!file_c)
        throw fstream::failure("Файл "+mFileCName+" не відкрився merge");

    int num1, num2;

    bool exit = false;
    bool exit_b = false;
    bool exit_c = false;

    file_b.read(reinterpret_cast<char*>(&num1), sizeof (num1));
    file_c.read(reinterpret_cast<char*>(&num2), sizeof (num2));

    while (!exit) {
        int i_b = 0;
        int i_c = 0;

        while (i_b < step and i_c < step) {
            if (exit_c) {
                do
                    file_a.write(reinterpret_cast<char *>(&num1), sizeof(num1));
                while (file_b.read(reinterpret_cast<char *>(&num1), sizeof(num1)) and i_b < step);

                exit_b = true;
                i_b++;
                break;
            }
            while (num1 <= num2 and !exit_b and i_b < step) {
                file_a.write(reinterpret_cast<char *>(&num1), sizeof(num1));
                if (!file_b.read(reinterpret_cast<char *>(&num1), sizeof(num1)))
                    exit_b = true;
                i_b++;
            }

            if (exit_b) {
                do {
                    file_a.write(reinterpret_cast<char *>(&num2), sizeof(num2));
                    i_c++;
                } while (file_c.read(reinterpret_cast<char *>(&num2), sizeof(num2)) and i_c < step);

                exit_c = true;
                break;
            }
            while (num1 > num2 and !exit_c and i_c < step) {
                file_a.write(reinterpret_cast<char *>(&num2), sizeof(num2));
                if (!file_c.read(reinterpret_cast<char *>(&num2), sizeof(num2)))
                    exit_c = true;
                i_c++;
            }

        }
        while (i_b++ < step and !exit_b) {
            file_a.write(reinterpret_cast<char *>(&num1), sizeof(num1));
            if (!file_b.read(reinterpret_cast<char *>(&num1), sizeof(num1)))
                exit_b = true;
        }

        while (i_c++ < step and !exit_c) {
            file_a.write(reinterpret_cast<char *>(&num2), sizeof(num2));
            if (!file_c.read(reinterpret_cast<char *>(&num2), sizeof(num2)))
                exit_c = true;
        }
        if (exit_b and exit_c)
            exit = true;
    }



    file_a.close();
    file_b.close();
    file_c.close();
}

