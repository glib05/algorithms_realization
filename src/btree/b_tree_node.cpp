#include "b_tree_node.h"
#include <stdexcept>

BTreeNode::BTreeNode(const int &level) {
    if (level < 4){
        throw invalid_argument("Too small level value");
    }

    mFather = nullptr;
    mLevel = level;
}

BTreeNode::~BTreeNode() {
    for (auto &child : mChildren){
        delete child;
    }
    mChildren.clear();
    mValues.clear();
    mFather = nullptr;
}

bool BTreeNode::isFool() {
    if (mChildren.size() == mLevel) {
        return true;
    }
    else {
        return false;
    }
}

void BTreeNode::insert(const int &value) {
    if (mChildren.size() == mLevel) {
        throw out_of_range("insert cannot be preformed: node is fool");
    }

    if (mValues.empty()){
        mChildren.push_back(nullptr);
        mChildren.push_back(nullptr);
        mValues.push_back(value);
    }
    else {
        int i = 1;
        for (auto it = mValues.begin() ; it != mValues.end(); it++, i++) {
            if ((*it) > value){
                mValues.insert(it, value);
                mChildren.insert(mChildren.begin() + i, nullptr);
                break;
            }
            else if (it+1 == mValues.end()){
                mValues.push_back(value);
                mChildren.push_back(nullptr);
                break;
            }
        }
    }
}

void BTreeNode::splitChild(BTreeNode *child) {
    if (child->mChildren.size() != mLevel){
        throw runtime_error("split cannot be performed: child is not full");
    }

    int middle = (mLevel-1)/2;
    int value = child->mValues[middle];

    this->insert(value);

    auto *child2 = new BTreeNode(mLevel);
    child2->mChildren.push_back(child->mChildren[middle+1]);
    if (child2->mChildren[0] != nullptr) {
        child2->mChildren[0]->mFather = child2;
    }
    child2->mFather = child->mFather;
    int j = 1;
    for (int i = middle+1; i < mLevel-1; i++, j++){
        child2->mValues.push_back(child->mValues[i]);
        child2->mChildren.push_back(child->mChildren[i+1]);
        if (child2->mChildren[j] != nullptr) {
            child2->mChildren[j]->mFather = child2;
        }
    }

    for (auto & ch : this->mChildren) {
        if (ch == nullptr) {
            ch = child2;
            break;
        }
    }

    child->mChildren.erase(child->mChildren.begin()+middle+1, child->mChildren.end());
    child->mValues.erase(child->mValues.begin()+middle, child->mValues.end());

    if (this->mValues[0] == value){
        mChildren[0] = child;
        mChildren[1] = child2;
    }
}

BTreeNode *BTreeNode::findEldestToSplit() {
    BTreeNode *eldest_to_split = nullptr;
    if (this->isFool()){
        eldest_to_split = this;
        if (this->mFather != nullptr){
            BTreeNode *probably_eldest_to_split = this->mFather->findEldestToSplit();
            if (probably_eldest_to_split != nullptr) {
                eldest_to_split = probably_eldest_to_split;
            }
        }
    }

    return eldest_to_split;
}

std::ostream &operator<<(ostream &out, const BTreeNode &node) {
    out<<char(219);
    for (auto value : node.mValues){
        out<<value<<char(219);
    }

    return out;
}

vector<BTreeNode *> BTreeNode::getAllNodesOnDepth(const int &depth) {
    vector<BTreeNode*> all_nodes;

    if (depth == 1){
        all_nodes.push_back(this);
        return all_nodes;
    }
    else if (this->mChildren[0] != nullptr){
        for (auto &child : this->mChildren){
            auto nodes = child->getAllNodesOnDepth(depth-1);
            all_nodes.insert(all_nodes.end(), nodes.begin(), nodes.end());
        }
    }

    return all_nodes;
}

const vector<int> &BTreeNode::getMValues() const {
    return mValues;
}
