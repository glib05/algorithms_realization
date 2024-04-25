#include "wild_ant.h"

int WildAnt::choose_path(const int &point, const AntGraph &graph) {
    srand(time(nullptr));
    int path;
    do{
        path = rand() % graph.mN;
    } while (find(mVisited.begin(), mVisited.end(), path) != mVisited.end());

    return path;
}