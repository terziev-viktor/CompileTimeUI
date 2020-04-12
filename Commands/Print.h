#ifndef _PRINT_H_
#define _PRINT_H_
#include "Trigger.h"

struct Print
{
    inline Trigger GetTrigger() { return "Print"; }

    void operator()(char **, int);
};

#endif