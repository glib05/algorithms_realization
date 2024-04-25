#include "queen.h"
#include <cmath>

Queen::Queen(const int &row_, const int &column_) {
    mRow = row_;
    mColumn = column_;
}

int Queen::getColumn() const {
    return mColumn;
}

int Queen::getRow() const {
    return mRow;
}

void Queen::setColumn(int column) {
    mColumn = column;
}

void Queen::setRow(int row) {
    mRow = row;
}

bool Queen::isAttacking(const Queen &other) const {
    if (mRow < 0 || other.mRow < 0)
        return false;
    return (mRow == other.mRow || mColumn == other.mColumn || abs(mRow - other.mRow) == abs(mColumn - other.mColumn));
}

Queen Queen::take() {
    Queen temp_q = *this;
    setRow(-1);
    setColumn(-1);
    return temp_q;
}

void Queen::put(const int &row, const int &column) {
    setRow(row);
    setColumn(column);
}

bool Queen::operator==(const Queen &other) const {
    if (mRow == other.mRow and mColumn == other.mColumn)
        return true;
    return false;
}
