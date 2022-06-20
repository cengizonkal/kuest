#ifndef KUEST_OPTION_H
#define KUEST_OPTION_H

struct Option {
    const char *text;
    //if successful this will be set to the next story
    struct Story *next;
    //if unsuccessful this will be set to the next story
    struct Story *failure;
};
#endif //KUEST_OPTION_H
