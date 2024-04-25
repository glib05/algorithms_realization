
#ifndef PRO_ALG_4_TRAVEL_ANTS_WILD_ANT_H
#define PRO_ALG_4_TRAVEL_ANTS_WILD_ANT_H

#include "ant.h"

class WildAnt: public Ant{
protected:
    int choose_path(const int& point, const AntGraph &graph) override;
public:
    explicit WildAnt(const int &start) : Ant(start) {};

    friend class ACO;
};

#endif //PRO_ALG_4_TRAVEL_ANTS_WILD_ANT_H