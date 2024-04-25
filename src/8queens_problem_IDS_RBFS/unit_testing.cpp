#include "unit_testing.h"
#include <conio.h>

void unitTestingQueensProblemAlgorithms(){
    system("cls");

    UnitTest test1("Generation board with given size 8", []()->bool{
        Board given_size_board(8);
        if (given_size_board.getMBoardSize() == 8)
            SUCCESS;
        else
            FAILURE;
    });

    UnitTest test2("Generation board with given size 11", []()->bool{
        Board given_size_board(11);
        if (given_size_board.getMBoardSize() == 11)
            SUCCESS;
        else
            FAILURE;
    });

    UnitTest test3("Generation board with no given size", []()->bool{
        Board no_given_size_board;
        if (no_given_size_board.getMBoardSize() == 8)
            SUCCESS;
        else
            FAILURE;
    });

    UnitTest test4("Generation board with wrong given size", []()->bool{
        try{
            Board wrong_given_size_board(-8);
        }
        catch (invalid_argument &) {
            SUCCESS;
        }
        FAILURE;
    });

    UnitTest test5("Generation board by given queens position", []()->bool{
        vector<Queen> queens_position_vector = {Queen(0, 0),
                                                Queen(7,1),
                                                Queen(0,1),
                                                Queen(0,5),
                                                Queen(6,5),
                                                Queen(4,0),
                                                Queen(3,2),
                                                Queen(1,5)};
        Board given_queens_board(queens_position_vector);
        if (given_queens_board.getMQueensVector() == queens_position_vector){
            SUCCESS;
        }
        else{
            FAILURE;
        }
    });

    UnitTest test6("Given wrong queens position", []()->bool{
        try {
            vector<Queen> queens_position_vector = {Queen(1, 1000),
                                                    Queen(7, 1),
                                                    Queen(-1, 1),
                                                    Queen(0, 5)};
            Board given_queens_board(queens_position_vector);
        }
        catch (invalid_argument &){
            SUCCESS;
        }
        FAILURE;
    });

    UnitTest test7("IDS solve", []()->bool{
        vector<Queen> queens_position_vector = {Queen(1, 1),
                                                Queen(1,2),
                                                Queen(2,0),
                                                Queen(3,3),
                                                Queen(3,6),
                                                Queen(4,3),
                                                Queen(6,4),
                                                Queen(6,7)};
        Board board_to_solve_IDS(queens_position_vector);
        if (board_to_solve_IDS.solveIDS())
            SUCCESS;
        else
            FAILURE;

    });

    UnitTest test8("IDS fail", []()->bool{
        vector<Queen> queens_position_vector = {Queen(0, 0),
                                                Queen(1,3),
                                                Queen(3,1),
                                                Queen(3,2)};
        Board board_to_solve_IDS(queens_position_vector);
        if (board_to_solve_IDS.solveIDS())
            FAILURE;
        else
            SUCCESS;

    });

    UnitTest test9("IDS solve random generate board", []()->bool{
        try {
            Board board_to_solve_IDS(8);
            board_to_solve_IDS.solveIDS();
        }
        catch (exception &){
            FAILURE;
        }
        SUCCESS;
    });

    UnitTest test10("IDS with unsolvable board", []()->bool{
        Board unsolvable_board(3);
        if (unsolvable_board.solveIDS())
            FAILURE;
        else
            SUCCESS;
    });

    UnitTest test11("RBFS solve", []()->bool{
        vector<Queen> queens_position_vector = {Queen(1, 1),
                                                Queen(1,2),
                                                Queen(2,0),
                                                Queen(3,3),
                                                Queen(3,6),
                                                Queen(4,3),
                                                Queen(6,4),
                                                Queen(6,7)};
        Board board_to_solve_IDS(queens_position_vector);
        if (board_to_solve_IDS.solveRBFS())
            SUCCESS;
        else
            FAILURE;
    });

    UnitTest test12("RBFS solve random generate board", []()->bool{
        Board board_to_solve_IDS(8);
        if(board_to_solve_IDS.solveRBFS())
            SUCCESS;
        else
            FAILURE;
    });

    UnitTest test13("RBFS with unsolvable board", []()->bool{
        Board unsolvable_board(3);
        if (unsolvable_board.solveRBFS())
            FAILURE;
        else
            SUCCESS;
    });

    runAllTests();
    getch();
}