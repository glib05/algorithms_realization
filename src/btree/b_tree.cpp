#include "b_tree.h"

BTree::BTree(const int &level) {
    mLevel = level;
    mRoot = new BTreeNode(mLevel);
}

BTree::~BTree() {
    delete mRoot;
}

BTreeNode *BTree::findNodeToInsert(const int &value) {
    if (mRoot->mValues.empty()){
        return mRoot;
    }

    BTreeNode *current_node = mRoot;

    bool exit = false;
    while (!exit) {
        for (int i = 0; i < current_node->mValues.size(); i++) {
            if ((value) <= (current_node->mValues[i])) {
                if (current_node->mChildren[i] == nullptr) {
                    exit = true;
                    break;
                }
                else {
                    current_node = current_node->mChildren[i];
                    break;
                }
            }
            else if (i == current_node->mValues.size()-1){
                if (current_node->mChildren[i+1] == nullptr) {
                    exit = true;
                    break;
                }
                else{
                    current_node = current_node->mChildren[i+1];
                    break;
                }
            }
        }
    }
    return current_node;
}

void BTree::insert(const int &value) {
    BTreeNode *node_to_insert = findNodeToInsert(value);

    if (node_to_insert->isFool()){
        BTreeNode *node_to_split = node_to_insert->findEldestToSplit();

        bool need_to_pop = false;
        if (node_to_split == mRoot){
            mRoot->mFather = new BTreeNode(mLevel);
            mRoot->mFather->mChildren.push_back(mRoot);
            mRoot = mRoot->mFather;
            need_to_pop = true;
        }

        while (node_to_split != nullptr){
            node_to_split->mFather->splitChild(node_to_split);
            node_to_split = node_to_insert->findEldestToSplit();
        }

        if (need_to_pop){
            mRoot->mChildren.pop_back();
        }
    }

    node_to_insert = findNodeToInsert(value);
    node_to_insert->insert(value);
}

BTreeNode *BTree::search(const int &value) {
    BTreeNode *current_node = mRoot;

    bool exit  = false;
    while (!exit) {
        for (int i = 0; i < current_node->mValues.size(); i++){
            if (value == current_node->mValues[i]){
                exit = true;
                break;
            }
            else if ((value) < (current_node->mValues[i])){
                if (current_node->mChildren[i] == nullptr){
                    current_node = nullptr;
                    exit = true;
                    break;
                }
                else{
                    current_node = current_node->mChildren[i];
                    break;
                }
            }
            else if (i + 1 == current_node->mValues.size()){
                if (current_node->mChildren[i+1] == nullptr){
                    current_node = nullptr;
                    exit = true;
                    break;
                }
                else {
                    current_node = current_node->mChildren[i+1];
                    break;
                }
            }
        }
    }

    return current_node;
}

std::ostream &operator<<(ostream &out, const BTree &tree) {
    int depth = 1;
    vector<BTreeNode *> nodes_on_depth = tree.mRoot->getAllNodesOnDepth(depth++);
    do{
        if (depth >5){
            out<<"TOO DEEP\n";
            break;
        }
        for (auto node : nodes_on_depth){
            out<<*node<<"  ";
        }
        out<<endl;

        nodes_on_depth = tree.mRoot->getAllNodesOnDepth(depth++);
    }while (!nodes_on_depth.empty());

    return out;
}