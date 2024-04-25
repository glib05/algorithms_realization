#include <vector>
#include <algorithm>
#include "ant_graph.h"

using namespace std;

#ifndef PRO_ALG_4_TRAVEL_ANTS_ANT_H
#define PRO_ALG_4_TRAVEL_ANTS_ANT_H

class Ant {
protected:
    int mStart;
    vector<int> mVisited;

    vector<double> getProbabilitiesToMove(const int& point, const AntGraph &graph);
    double getSumaForP(const int& point, const AntGraph &graph);

    virtual int choose_path(const int& point, const AntGraph &graph);
public:
    explicit Ant(const int & start);

    vector<int> goThrough(const AntGraph &graph);

    friend class ACO;
};

#endif //PRO_ALG_4_TRAVEL_ANTS_ANT_H