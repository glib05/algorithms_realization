#include <iostream>
#include <vector>
#include "queen.h"

#ifndef PRO_ALG_2_QUEENS_BOARD_H
#define PRO_ALG_2_QUEENS_BOARD_H

struct RBFSReturnedValues;
struct BoardNode;



class Board{
    unsigned int mBoardSize;
    std::vector<Queen> mQueensVector;

    int countAttackingPairs() const;

    bool isSafe(const int &row, const int &column);
public:

    explicit Board(const int &size = 8);
    explicit Board(const std::vector<Queen>& queens_vector);
    Board(const Board &other);

    unsigned int getMBoardSize() const;
    const std::vector<Queen> &getMQueensVector() const;

    friend Board solveDLS(int depth, Board& board);
    bool solveIDS();

    bool solveRBFS();
    friend RBFSReturnedValues RBFS(Board &board, BoardNode &node, int f_limit);

    friend std::ostream& operator<<(std::ostream& out,const Board &board);
};

struct RBFSReturnedValues{
    bool fail;
    int f_limit;
    Board board;

    RBFSReturnedValues() = default;
    RBFSReturnedValues(bool fail, int f_limit, const Board &board): fail(fail), f_limit(f_limit), board(board) {};
};

struct BoardNode{
    Board board;
    int f;
    int g;

    BoardNode(): f(1000000000) {};
    BoardNode(const Board &board, int f, int g) : board(board), f(f), g(g) {};
};

#endif //PRO_ALG_2_QUEENS_BOARD_H

