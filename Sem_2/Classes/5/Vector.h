#pragma once
#include "Object.h"
#include <iostream>
#include <string>

class Vector
{
  public:
    Vector(void);
    Vector(int);

    ~Vector(void);
    void Add(Object *);
    friend std::ostream &operator<<(std::ostream &out, const Vector &);

  private:
    Object **beg;
    int size;
    int cur;
};
