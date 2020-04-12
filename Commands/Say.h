#ifndef _SAY_H_
#define _SAY_H_
#include "Trigger.h"

struct Say
{
    inline Trigger GetTrigger() { return "Say"; }

    void operator()(char **, int);
};


#endif