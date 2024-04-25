#include "unit_testing.h"
#include <random>
#include <conio.h>

void unitTestingBTree(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(-1000000, 10000000);

    system("cls");

    UnitTest test1("Generation and fill B-Tree with t = 4", [&distribution, &gen]()->bool{
        try {
            BTree tree(4);

            int numbers[1000];

            for (int & number : numbers) {
                number = distribution(gen);
                tree.insert(number);
            }

            for (auto &number : numbers){
                if (tree.search(number) == nullptr){
                    FAILURE;
                }
            }

            SUCCESS;
        }
        catch(exception &e){
            FAILURE;
        }
    });

    UnitTest test2("Generation and fill B-Tree with t = 10", [&distribution, &gen]()->bool{
        try {
            BTree tree(10);

            int numbers[10000];

            for (int & number : numbers) {
                number = distribution(gen);
                tree.insert(number);
            }

            for (auto &number : numbers){
                if (tree.search(number) == nullptr){
                    FAILURE;
                }
            }

            SUCCESS;
        }
        catch(exception &e){
            FAILURE;
        }
    });

    UnitTest test3("Generation and fill B-Tree with t = 1000", [&distribution, &gen]()->bool{
        try {
            BTree tree(1000);

            int numbers[100000];

            for (int & number : numbers) {
                number = distribution(gen);
                tree.insert(number);
            }

            for (auto &number : numbers){
                if (tree.search(number) == nullptr){
                    FAILURE;
                }
            }

            SUCCESS;
        }
        catch(exception &e){
            FAILURE;
        }
    });

    UnitTest test4("Creating tree with wrong t", []()->bool{
        try{
            BTree tree(1);

            FAILURE;
        }
        catch(exception &e){
            SUCCESS;
        }
    });

    UnitTest test5("Searching in large data set", [&distribution, &gen]()->bool {
        try{
            BTree tree(10);

            for (int i = 0; i < 10000; i++){
                tree.insert(distribution(gen));
            }

            tree.insert(99);

            for (int i = 0; i < 10000; i++){
                tree.insert(distribution(gen));
            }

            if (tree.search(99) == nullptr){
                FAILURE;
            }

            SUCCESS;
        }
        catch(exception &e){
            FAILURE;
        }
    });

    runAllTests();
    getch();
}