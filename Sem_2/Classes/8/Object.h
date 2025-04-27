#pragma once
#include "Event.h"
#include <iostream>

class Object
{
  public:
    virtual void show() = 0;
    virtual void input() = 0;
    void HandleEvent(const TEvent &);
};