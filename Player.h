
#ifndef KUEST_PLAYER_H
#define KUEST_PLAYER_H

#include "Narrative.h"

class Player {

public:
    int skills[6] = {0, 0, 0, 0, 0, 0};
    int hp = 10;
    Narrative *currentNarrative{};
    void setCurrentNarrative(Narrative *n);
    void choose(int option);

};

#endif //KUEST_PLAYER_H
