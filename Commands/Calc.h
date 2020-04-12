#ifndef _CALC_H_
#define _CALC_H_
#include "Trigger.h"

struct Calc
{
    inline Trigger GetTrigger() { return "Calc"; }

    void operator()(char **, int);
};


#endif