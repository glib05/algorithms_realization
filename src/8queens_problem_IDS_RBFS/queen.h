
#ifndef PRO_ALG_2_QUEENS_QUEEN_H
#define PRO_ALG_2_QUEENS_QUEEN_H

class Queen{
private:
    int mRow;
    int mColumn;
public:
    explicit Queen(const int &row_ = 0, const int &column_ = 0);

    int getColumn() const;
    int getRow() const;
    void setColumn(int column);
    void setRow(int row);

    Queen take();
    void put(const int &row, const int &column);

    bool isAttacking(const Queen &other) const;

    bool operator==(const Queen &other) const;

    friend class Board;
};

#endif //PRO_ALG_2_QUEENS_QUEEN_H
