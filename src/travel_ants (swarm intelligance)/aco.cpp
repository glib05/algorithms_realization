#include "aco.h"
#include <iostream>

ACO::ACO(const int &graph_size, const int &a, const int &b, const double &p, const int &ants_quantity,
         const int &wild_ants_quantity) : mGraph(graph_size, a, b, p) {
    srand(time(nullptr));

    for (int i = 0; i < ants_quantity; i++){
        Ant *ant = new Ant(rand()%graph_size);
        mpAnts.push_back(ant);
    }


    for (int i = 0; i < wild_ants_quantity; i++){
        Ant *ant = new WildAnt(rand()%graph_size);
        mpAnts.push_back(ant);
    }
}

ACO::~ACO() {
    for (auto &v : mpAnts){
        delete v;
    }
}

const AntGraph &ACO::getMGraph() const {
    return mGraph;
}

void ACO::runIteration() {
    randomise_start_for_ants();

    vector<vector<int>> ants_paths;

    for (auto ant : mpAnts){
        ants_paths.push_back(ant->goThrough(mGraph));
    }

    mGraph.updatePheromone(ants_paths);
}

vector<int> ACO::findMinPathByPheromone() {
    return mGraph.findMinPathByPheromone();
}

int ACO::countMinLByPheromone() {
    return mGraph.countMinLByPheromone();
}

int ACO::countLByPath(const vector<int> &path) {
    return mGraph.countLByPath(path);
}

void ACO::randomise_start_for_ants() {
    for (auto ant : mpAnts){
        ant->mStart = rand()%mGraph.mN;
    }
}