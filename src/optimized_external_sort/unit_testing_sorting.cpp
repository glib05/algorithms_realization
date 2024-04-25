#include "unit_testing_sorting.h"
#include <fstream>
#include <conio.h>
#include "my_unit_test.h"
#include "merge_sort.h"
#include "file_functions.h"
#include "external_sort.h"

#define GB 1073741824 // 268 435 456

void unitTestingSorting(){
    system("cls");

    UnitTest test1("Генерація файлу з випадковими числами", []()->bool{
        const int size = 100;

        createFileWithRandomNumbers("A.bin", size);

        ifstream file("A.bin", ios::in | ios::binary);

        int num;
        int i = 0;
        while(file.read(reinterpret_cast<char *>(&num), sizeof(num)))
            i++;

        if (i == size)
            SUCCESS;
        else
            FAILURE;
    });

    UnitTest test2("Привильність сортування", []()->bool{
        const int size = 100;

        createFileWithRandomNumbers("A.bin", size);

        ExternalSimpleFileSort("A.bin");

        int num, num_next;

        ifstream file("A.bin", ios::in | ios::binary);
        file.read(reinterpret_cast<char *>(&num), sizeof(num));
        while (file.read(reinterpret_cast<char *>(&num_next), sizeof(num_next))){
            if (num > num_next)
                FAILURE;
            num = num_next;
        }

        SUCCESS;
    });

    UnitTest test3("Швидкість сортування (1 ГБ/3 хв)", []()->bool{
        const int size = GB/ sizeof(int);


        createFileWithRandomNumbers("A.bin", size);

        auto start_time = chrono::high_resolution_clock::now();
        ExternalSimpleFileSort("A.bin");
        chrono::duration<double> elapsed = chrono::high_resolution_clock::now() - start_time;

        if (elapsed.count() < 180)
            SUCCESS;
        else
            FAILURE;
    });

    runAllTests();
    getch();
}
