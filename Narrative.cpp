#include "Narrative.h"

void Narrative::print() {
    std::cout << text << std::endl;
    //print options
    for (int i = 0; i < options.size(); i++) {
        std::cout << i << ". ";
        options[i].print();
    }
}
