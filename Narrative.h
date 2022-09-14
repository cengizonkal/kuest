#ifndef KUEST_NARRATIVE_H
#define KUEST_NARRATIVE_H

#include <iostream>
#include <vector>
#include "Option.h"

class Narrative {
public:
    int id = 0;
    std::string text;
    std::vector<Option> options;
    void print();
};


#endif //KUEST_NARRATIVE_H
