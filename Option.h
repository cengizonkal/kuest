//
// Created by cengiz on 14.09.2022.
//

#ifndef KUEST_OPTION_H
#define KUEST_OPTION_H

#include <iostream>
#include "Skills.h"
class Narrative;

class Option {
public:
    std::string text;
    Skills required_skill{};
    int dc{};
    Narrative *success{};
    Narrative *failure{};
    void print() const;

};

#endif //KUEST_OPTION_H
