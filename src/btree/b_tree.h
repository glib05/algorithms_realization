#include "b_tree_node.h"

#ifndef PRO_ALG_3_BTREE_B_TREE_H
#define PRO_ALG_3_BTREE_B_TREE_H

class BTree{
    int mLevel;

    BTreeNode *mRoot;
public:
    explicit BTree(const int &level);
    ~BTree();

    BTreeNode *findNodeToInsert(const int &value);
    void insert(const int &value);

    BTreeNode *search(const int &value);

    friend std::ostream &operator<<(std::ostream &out, const BTree &tree);
};

#endif //PRO_ALG_3_BTREE_B_TREE_H
