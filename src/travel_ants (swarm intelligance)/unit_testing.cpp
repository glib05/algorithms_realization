#include "unit_testing.h"

void unit_testing(){
    system("cls");

    UnitTest test6("20 iterations on VERY big graph size", []()->bool {
        try{
            ACO ant_colony(400, 2, 4, 0.7, 30, 15);
            for (int i = 0; i < 20; i++){
                ant_colony.runIteration();
            }

            SUCCESS;
        }
        catch (exception &e){
            FAILURE;
        }
    });

    UnitTest test1("Creating ant graph", []()->bool {
        try {
            AntGraph graph(1000, 3, 4, 0.9);
            double **visibility = graph.getMVisibility();
            for (int i = 0; i < 1000; i++) {
                for (int j = 0; j < 1000; j++) {
                    if (i == j) {
                        if (visibility[i][j] != 0) {
                            FAILURE;
                        }
                    } else {
                        if (visibility[i][j] == 0) {
                            FAILURE;
                        }
                    }
                }
            }
            SUCCESS;
        }
        catch (exception &e){
            FAILURE;
        }
    });

    UnitTest test2("Working of algorithm with no wild ants", []()->bool {
        try {
            ACO ant_colony(50, 1, 4, 0.5, 10, 0);
            for (int i = 0; i < 400; i++) {
                ant_colony.runIteration();
            }

            if (ant_colony.countMinLByPheromone() < 0){
                FAILURE;
            }
            else{
                SUCCESS;
            }
        }
        catch (exception &e){
            FAILURE;
        }
    });

    UnitTest test3("Working of algorithm with wild ants", []()->bool {
        try {
            ACO ant_colony(50, 1, 4, 0.5, 10, 5);
            for (int i = 0; i < 400; i++) {
                ant_colony.runIteration();
            }

            if (ant_colony.countMinLByPheromone() < 0){
                FAILURE;
            }
            else{
                SUCCESS;
            }
        }
        catch (exception &e){
            FAILURE;
        }
    });

    UnitTest test4("Working of algorithm with only wild ants", []()->bool {
        try {
            ACO ant_colony(50, 1, 4, 0.5, 0, 15);
            for (int i = 0; i < 400; i++) {
                ant_colony.runIteration();
            }

            if (ant_colony.countMinLByPheromone() < 0){
                FAILURE;
            }
            else{
                SUCCESS;
            }
        }
        catch (exception &e){
            FAILURE;
        }
    });

    UnitTest test5("Creating ant graph with wrong arguments", []()->bool {
        try{
            AntGraph graph(1000, 5, -1, 100);
        }
        catch (exception &e){
            SUCCESS;
        }
        FAILURE;
    });

    runAllTests();
}