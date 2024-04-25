#include <iostream>
#include <vector>
#include <conio.h>
#include "b_tree.h"
#include <random>
#include "unit_testing.h"

#define ENTER 13
#define ESCAPE 27
#define SPACE 32

using namespace std;

void runProgram();

int main(int argc, char **argv) {
    if (argc == 1){
        runProgram();
    }
    else if (string(argv[1]) == "test"){
        unitTestingBTree();
    }

    return 0;
}

void runProgram(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(-10000, 10000);

    try {
        char input;

        do {
            system("cls");

            BTree tree(4);

            tree.insert(200);
            tree.insert(250);
            tree.insert(50);
            tree.insert(40);
            tree.insert(30);
            tree.insert(1);
            tree.insert(21);
            tree.insert(10001);
            tree.insert(11);
            tree.insert(999);
            tree.insert(10);
            tree.insert(4635);

            for (int i = 0; i < 100; i++) {
                tree.insert(distribution(gen));
            }

            if (tree.search(1) != nullptr)
                cout << "was find number 1\n";
            if (tree.search(60) != nullptr)
                cout << "was find number 60\n";
            if (tree.search(-2548) != nullptr)
                cout << "was find number -2548\n";
            if (tree.search(-31) != nullptr)
                cout << "was find number -31\n";

            cout << "\n\nIf you want to see nodes of B-Tree pres ENTER\n"
                    "If you want to restart press SPACE\n"
                    "If you want to exit press ESCAPE" << endl;
            while ((input = getch()) != ENTER and input != ESCAPE and input != SPACE);

            if (input == ENTER){
                cout<<tree;

                cout << "\n\nIf you want to restart press SPACE\n"
                        "If you want to exit press ESCAPE" << endl;
                while ((input = getch()) != ESCAPE and input != SPACE);
            }
        }while(input != ESCAPE);
    }
    catch (exception &e){
        cout<<e.what();
        getch();
    }
}