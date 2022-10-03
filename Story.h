#ifndef KUEST_STORY_H
#define KUEST_STORY_H
#include "Narrative.h"
#include <sqlite3.h>
class Story {
    std::vector<Narrative> narratives;
public:
    void loadNarratives();

    Narrative *getNarrative(int id) {
        return &narratives[id];
    }


};
#endif //KUEST_STORY_H
