#include "Player.h"
#include <iostream>

void Player::choose(int option) {
    //check if option is valid
    if (option < 0 || option >= currentNarrative->options.size()) {
        std::cout << "Invalid option" << std::endl;
        return;
    }
    //check if skill is high enough
    if (skills[currentNarrative->options[option].required_skill] >= currentNarrative->options[option].dc) {
        //success
        currentNarrative = currentNarrative->options[option].success;
    } else {
        //failure
        currentNarrative = currentNarrative->options[option].failure;
    }

}

void Player::setCurrentNarrative(Narrative *n) {currentNarrative = n;}
