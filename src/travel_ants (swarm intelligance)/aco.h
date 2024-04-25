#ifndef PRO_ALG_4_TRAVEL_ANTS_ACO_H
#define PRO_ALG_4_TRAVEL_ANTS_ACO_H

#include "ant.h"
#include "wild_ant.h"
#include "ant_graph.h"

class ACO{
    AntGraph mGraph;
    vector<Ant*> mpAnts;

    void randomise_start_for_ants();
public:
    explicit ACO(const int &graph_size = 200, const int &a = 2, const int &b = 4, const double &p=0.7,
        const int &ants_quantity=30, const int &wild_ants_quantity=15);
    ~ACO();

    const AntGraph &getMGraph() const;

    void runIteration();

    vector<int> findMinPathByPheromone();
    int countMinLByPheromone();
    int countLByPath(const vector<int>& path);
};

#endif //PRO_ALG_4_TRAVEL_ANTS_ACO_H