#include <vector>
#include <random>
#include <ctime>
#include <iostream>

using namespace std;

#ifndef PRO_ALG_4_TRAVEL_ANTS_GRAPH_H
#define PRO_ALG_4_TRAVEL_ANTS_GRAPH_H

class AntGraph{
protected:
    int mN;
    int mA;
    int mB;
    double mP;

    double **mVisibility;
    double **mPheromone;

    void fillVisibilityRandomly();
    void fillPheromoneRandomly();

    void updatePheromone(vector<vector<int>> &ants_paths);

public:
    AntGraph(int n, int a, int b, double p);
    ~AntGraph();

    double **getMVisibility() const;

    vector<int> findMinPathByPheromone();
    int countMinLByPheromone();
    int countLByPath(const vector<int>& path);

    friend ostream& operator<<(ostream& out,const AntGraph &graph);

    friend class Ant;
    friend class WildAnt;
    friend class ACO;
};

#endif //PRO_ALG_4_TRAVEL_ANTS_GRAPH_H