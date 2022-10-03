#include <iostream>
#include "Player.h"
#include "Story.h"


int main() {

    Story story;
    story.loadNarratives();

    Player player;
    player.setCurrentNarrative(story.getNarrative(0));
    while (!player.currentNarrative->options.empty()) {
        player.currentNarrative->print();
        int choice;
        std::cin >> choice;
        player.choose(choice);
    }


    return 0;
}
