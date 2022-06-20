#ifndef KUEST_STORY_H
#define KUEST_STORY_H
#include "Option.h"
struct Story {
    //text to display
    const char *text;
    struct Option *options;
};
#endif //KUEST_STORY_H
