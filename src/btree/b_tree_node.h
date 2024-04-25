#include <vector>
#include <iostream>
#include <functional>

#ifndef PRO_ALG_3_BTREE_B_TREE_NODE_H
#define PRO_ALG_3_BTREE_B_TREE_NODE_H

using namespace std;

class BTreeNode{
    int mLevel;

    BTreeNode *mFather;

    vector<int> mValues;
    vector<BTreeNode*> mChildren;

    explicit BTreeNode(const int &level);
    ~BTreeNode();

    bool isFool();
    void insert(const int &value);

    void splitChild(BTreeNode *child);

    BTreeNode* findEldestToSplit();

    friend std::ostream& operator<<(std::ostream& out,const BTreeNode &node);

    friend class BTree;

public:
    vector<BTreeNode*> getAllNodesOnDepth(const int &depth);

    const vector<int> &getMValues() const;
};

#endif //PRO_ALG_3_BTREE_B_TREE_NODE_H
