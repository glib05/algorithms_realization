#include "ant_graph.h"
#include <algorithm>
#include <iomanip>

using namespace std;

AntGraph::AntGraph(int n, int a, int b, double p) {
    if (p >= 1 or p <= 0){
        throw invalid_argument("Wrong p");
    }

    mN = n;
    mA = a;
    mB = b;
    mP = p;

    srand(time(nullptr));

    mVisibility = new double * [mN];
    mPheromone = new double * [mN];
    for (int i = 0; i < mN; i++){
        mVisibility[i] = new double [mN];
        mPheromone[i] = new double [mN];
    }

    fillVisibilityRandomly();
    fillPheromoneRandomly();
}

AntGraph::~AntGraph() {
    for (int  i = 0; i < mN; i++){
        delete[] mVisibility[i];
        delete[] mPheromone[i];
    }
    delete[] mVisibility;
    delete[] mPheromone;
}

void AntGraph::fillVisibilityRandomly() {
    for (int i = 0; i < mN; i++){
        for (int j = 0; j < mN; j++){
            if (i == j){
                mVisibility[i][j] = 0;
            }
            else{
                mVisibility[i][j] = 1.0 / (rand() % 40 + 1);
            }
        }
    }
}

void AntGraph::fillPheromoneRandomly() {
    for (int i = 0; i < mN; i++){
        for (int j = 0; j < mN; j++){
            if (i == j){
                mPheromone[i][j] = 0;
            }
            else{
                mPheromone[i][j] =(rand()%3+1)/10.0;
            }
        }
    }
}

vector<int> AntGraph::findMinPathByPheromone() {
    vector<int> minPath;

    double max_pheromone = 0;
    int i_max = 0;
    int j_max = 0;

    for (int i = 0; i < mN; i++){
        for (int j = 0; j < mN; j++){
            if (max_pheromone <  mPheromone[i][j]){
                max_pheromone = mPheromone[i][j];
                i_max = i;
                j_max = j;
            }
        }
    }

    minPath.push_back(i_max);
    minPath.push_back(j_max);

    i_max = j_max;

    while (minPath.size() < mN){
        max_pheromone = 0;

        for (int j = 0; j < mN; j++){
            if (find(minPath.begin(), minPath.end(), j) == minPath.end()) {
                if (max_pheromone < mPheromone[i_max][j]) {
                    max_pheromone = mPheromone[i_max][j];
                    j_max = j;
                }
            }
        }

        minPath.push_back(j_max);
        i_max = j_max;
    }

    minPath.push_back(minPath[0]);

    return minPath;
}

int AntGraph::countMinLByPheromone() {
    auto minPath = findMinPathByPheromone();

    double minL = 0;

    for (int i = 0; i < minPath.size()-1; i++) {
        if (mVisibility[minPath[i]][minPath[i + 1]] == 0) {
            minL += 40;
        } else{
            minL += 1 / mVisibility[minPath[i]][minPath[i + 1]];
        }
    }

    return int(minL);
}

int AntGraph::countLByPath(const vector<int> &path) {
    double l = 0;

    for (int i = 0; i < path.size()-1; i++){
        if (mVisibility[path[i]][path[i + 1]] == 0) {
            l += 40;
        } else{
            l += 1 / mVisibility[path[i]][path[i + 1]];
        }
    }

    return int(l);
}

void AntGraph::updatePheromone(vector<vector<int>> &ants_paths) {
    int l_min = countMinLByPheromone();

    for (int i = 0; i < mN; i++){
        for (int j = 0; j < mN; j++){
            mPheromone[i][j] = mPheromone[i][j]*(1-mP);
        }
    }

    for (auto & path : ants_paths){
        int  l = countLByPath(path);

        for (int h = 0; h < path.size() - 1; h++){
            mPheromone[path[h]][path[h + 1]] += double (l_min) / l;
        }
    }
}

ostream &operator<<(ostream &out, const AntGraph &graph) {
    if (graph.mN <=50) {
        cout << "   ";
        for (int i = 0; i < graph.mN; i++) {
            cout << "\033[33m" << setw(2) << i << "\033[0m" << " ";
        }
        cout << endl;

        for (int i = 0; i < graph.mN; i++) {
            out << "\033[33m" << setw(2) << i << "\033[0m" << " ";
            for (int j = 0; j < graph.mN; j++) {
                if (graph.mVisibility[i][j] == 0) {
                    out << "\033[31m" << setw(2) << 0 << "\033[0m" << " ";
                } else {
                    out << "\033[0m" << setw(2) << int(1 / graph.mVisibility[i][j]) << "\033[0m" << " ";
                }
            }
            out << endl;
        }
    }
    else{
        out<<"matrix is too big"<<endl;
    }
    return out;
}

double **AntGraph::getMVisibility() const {
    return mVisibility;
}