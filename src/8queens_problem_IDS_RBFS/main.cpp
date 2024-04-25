#include <iostream>
#include <conio.h>
#include "board.h"
#include "unit_testing.h"

#define ENTER 13
#define ESCAPE 27

using namespace std;

void doQueensProblem();

int main(int argc, char **argv) {

    if (argc == 1){
        doQueensProblem();
    }
    else if (string(argv[1]) == "test"){
        unitTestingQueensProblemAlgorithms();
    }
}

void doQueensProblem(){
    char input;
    do {
        system("cls");

        Board b1(8);

        cout << "Initial chessboard:\n"<< b1 << endl;

        cout<<"Choose algoritm: IDS - 1, RBFS - 2";

        do{
            input = getch();
        }while(input != '1' and input != '2');

        if (input == '1') {
            cout<<"\nIDS\n";
            if (!b1.solveIDS())
                cout << "\nThe IDS failed to solve this problem\n";
            else
                cout << "\nResult chessboard by IDS:\n" << b1 << endl;
        }
        else{
            cout<<"\nRBFS\n";
            if (!b1.solveRBFS())
                cout << "\nThe RBFS failed to solve this problem\n";
            else
                cout << "\nResult chessboard by RBFS:\n" << b1 << endl;
        }

        cout << "\nTo exit press ESCAPE, to start over press ENTER";
        while((input = getch()) != ENTER and input != ESCAPE);

    }while(input != ESCAPE);
}

