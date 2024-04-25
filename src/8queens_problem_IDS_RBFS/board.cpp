#include "board.h"
#include <random>

using namespace std;

Board::Board(const int &size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, size-1);

    if (size<1){
        throw invalid_argument("Incorrect board size");
    }

    mBoardSize = size;
    for (int i = 0; i < size; i++) {
        mQueensVector.emplace_back(distribution(gen), distribution(gen));
    }

}

Board::Board(const std::vector<Queen>& queens_vector) {
    mBoardSize = queens_vector.size();

    for (auto queen : queens_vector){
        if (queen.getRow() < 0 or queen.getRow() >= queens_vector.size()){
            throw invalid_argument("Incorrect row");
        }
        if (queen.getColumn() < 0 or queen.getColumn() >= queens_vector.size()){
            throw invalid_argument("Incorrect column");
        }
    }

    mQueensVector = queens_vector;
}

Board::Board(const Board &other) {
    mBoardSize = other.mBoardSize;
    for (int i = 0; i < mBoardSize; i++)
        mQueensVector.push_back(other.mQueensVector[i]);
}

unsigned int Board::getMBoardSize() const {
    return mBoardSize;
}

const vector<Queen> &Board::getMQueensVector() const {
    return mQueensVector;
}

int Board::countAttackingPairs() const {
    int count = 0;
    for (int i = 0; i < mBoardSize; ++i) {
        for (int j = i + 1; j < mBoardSize; ++j) {
            if (mQueensVector[i].isAttacking(mQueensVector[j])) {
                count++;
            }
        }
    }
    return count;
}

bool Board::isSafe(const int &row, const int &column) {
    Queen new_queen(row, column);
    for (int i = 0; i < mBoardSize; i++)
        if (new_queen.isAttacking(mQueensVector[i]))
            return false;
    return true;
}

bool Board::solveIDS() {
    int i = 0;
    while (i < mBoardSize){
        Board solve_board(solveDLS(++i, *this));
        if (solve_board.mBoardSize != 1){
            *this = Board(solve_board);
            return true;
        }
    }
    return false;
}

Board solveDLS(int depth, Board &board) {
    if (board.countAttackingPairs() == 0) {
        return board;
    }
    if (depth == 0) {
        return Board(1);
    }

    for (int i = 0; i < board.mBoardSize; i++) {
        for (int row = 0; row < board.mBoardSize; row++) {
            for (int column = 0; column < board.mBoardSize; column++) {
                Board successor_board(board);
                successor_board.mQueensVector[i].take();
                if (successor_board.isSafe(row, column)) {
                    successor_board.mQueensVector[i].put(row, column);
                    Board solve_board(solveDLS(depth - 1, successor_board));
                    if (solve_board.mBoardSize != 1)
                        return solve_board;
                }
            }
        }
    }
    return Board(1);
}

bool Board::solveRBFS() {
    if (mBoardSize < 4)
        return false;

    BoardNode node(*this, countAttackingPairs(), 0);
    auto solution = RBFS(*this, node, 1000000000);

    *this = Board(solution.board);
    return !solution.fail;
}

RBFSReturnedValues RBFS(Board &board, BoardNode &node, int f_limit) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, board.mBoardSize-1);

    if (board.countAttackingPairs() == 0)
        return RBFSReturnedValues(false, 0, board);

    vector<BoardNode> successors;

    for (int i = 0; i < board.mBoardSize; i++){
        Board potential_successor(board);
        potential_successor.mQueensVector[i].take();
        bool break_var = false;
        for (int row = 0; row < board.mBoardSize; row++) {
            for (int column = 0; column < board.mBoardSize; column++) {
                if (potential_successor.isSafe(row, column)) {
                    potential_successor.mQueensVector[i].put(row, column);
                    break_var = true;
                    break;
                }
            }
            if (break_var)
                break;
        }
        if (!break_var)
            potential_successor.mQueensVector[i].put(distribution(gen), distribution(gen));
        successors.emplace_back(potential_successor, node.g+1 + potential_successor.countAttackingPairs(), node.g+1);

    }

    if (successors.empty())
        return RBFSReturnedValues(true, f_limit, board);

    for (BoardNode &s : successors){
        if (s.f < node.f)
            s.f = node.f;
    }

    while (true){
        int best_index = 0;
        for (int i = 0; i < successors.size(); i++)
            if (successors[best_index].f > successors[i].f)
                best_index = i;

        if (successors[best_index].f > f_limit)
            return RBFSReturnedValues(true, successors[best_index].f, successors[best_index].board);

        int second_best_index = (best_index+1)%successors.size();
        for (int i = 0; i < successors.size(); i++){
            if (successors[second_best_index].f > successors[i].f && best_index!=i)
                second_best_index = i;
        }

        RBFSReturnedValues result;
        if (successors[second_best_index].f < f_limit)
            result = RBFS(successors[best_index].board, successors[best_index], successors[second_best_index].f);
        else
            result = RBFS(successors[best_index].board, successors[best_index], f_limit);
        if (!result.fail)
            return result;
        successors[best_index].f = result.f_limit;
    }
}

std::ostream &operator<<(ostream &out, const Board &board) {
    int color = 0;
    int app = int(board.mBoardSize+1)%2;
    for (int row = 0; row < board.mBoardSize; row++){
        for (int column = 0; column < board.mBoardSize; column++) {
            bool found = false;
            for (int k = 0; k < board.mBoardSize; k++)
                if (board.mQueensVector[k].getRow() == row and board.mQueensVector[k].getColumn() == column){
                    found = true;
                    break;
                }
            if (found)
                out<<char(179)<<"\033[33mQ"<<"\033[0m";
            else if (color%2 == 0)
                out<<char(179)<<char(219);
            else
                out<<char(179)<<" ";
            color++;
        }
        color+=app;
        out<<char(179)<<endl;
    }
    return out;
}