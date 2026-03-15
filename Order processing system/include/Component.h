#ifndef Component_h
#define Component_h

#include "Unit.h"

class Component : public Unit
{
public:
    Component(int i = -1, int c = 0) : Unit(i, c) {}
};

#endif
