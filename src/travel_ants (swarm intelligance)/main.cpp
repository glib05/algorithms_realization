#include "aco.h"
#include "unit_testing.h"
#include <iostream>
#include <conio.h>

using namespace std;

void run_aco(ACO &ant_colony, const int &step = 20, const int &max_iteration = 1000);

int main(int argc, char **argv) {
    ACO ant_colony(200, 2, 4, 0.7, 30, 15);

    if (argc == 1){
        run_aco(ant_colony, 20, 1000);
    }
    else if (string(argv[1]) == "test"){
        unit_testing();
    }

    getch();
    return 0;
}

void run_aco(ACO &ant_colony, const int &step, const int &max_iteration){
    cout<<"Distance matrix of graph:\n"<<ant_colony.getMGraph()<<endl;

    int min_l = ant_colony.countMinLByPheromone();
    vector<int> min_path = ant_colony.findMinPathByPheromone();

    for (int i = 0; i < max_iteration; i++){
        ant_colony.runIteration();

        int l = ant_colony.countMinLByPheromone();
        if (l < min_l){
            min_l = l;
            min_path = ant_colony.findMinPathByPheromone();
        }
        if (i % 20 + 1 == step){
            cout<<i+1<<" iteration: L = "<<l<<endl;
        }
    }
    cout<<"Min L = "<<min_l<<endl;
    cout<<"Min path: ";
    for (auto &p : min_path){
        cout<<p<<" ";
    }
}