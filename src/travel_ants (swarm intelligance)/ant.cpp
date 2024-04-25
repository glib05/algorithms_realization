#include "ant.h"
#include <cmath>

Ant::Ant(const int &start) {
    mStart = start;
}

vector<int> Ant::goThrough(const AntGraph &graph) {
    mVisited.clear();
    mVisited.push_back(mStart);

    int point = mStart;
    bool exit = false;

    while (!exit){
        if (mVisited.size() == graph.mN){
            mVisited.push_back(mStart);
            exit = true;
        }
        else {
            int path = choose_path(point, graph);
            mVisited.push_back(path);
            point = path;
        }
    }

    return mVisited;
}

vector<double> Ant::getProbabilitiesToMove(const int& point, const AntGraph &graph) {
    vector<double> probabilities;

    double suma = getSumaForP(point, graph);
    if (suma == 0){
        suma = 1;
    }

    for (int i = 0; i < graph.mN; i++){
        if (find(mVisited.begin(), mVisited.end(), i) != mVisited.end()){
            probabilities.push_back(0);
        }
        else{
            double numerator = pow(graph.mPheromone[point][i], graph.mA) * pow(graph.mVisibility[point][i], graph.mB);
            probabilities.push_back(numerator/suma);
        }
    }
    return probabilities;
}

double Ant::getSumaForP(const int& point, const AntGraph &graph) {
    double suma = 0;
    for (int i = 0; i < graph.mN; i++){
        if (find(mVisited.begin(), mVisited.end(), i) != mVisited.end()){
            continue;
        }

        suma += pow(graph.mPheromone[point][i], graph.mA) * pow(graph.mVisibility[point][i], graph.mB);
    }
    return suma;
}

int Ant::choose_path(const int &point, const AntGraph &graph) {
    srand(time(nullptr));
    double rand_discrete = double(rand())/RAND_MAX;

    auto probabilities = getProbabilitiesToMove(point, graph);
    double prob = 0;

    for (int  i =0; i < probabilities.size(); i++){
         prob += probabilities[i];
        if (rand_discrete < prob){
            return i;
        }
    }

    return mStart;
}