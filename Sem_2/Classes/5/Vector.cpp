#include "Vector.h"

Vector::Vector(void)
{
    beg = 0;
    size = 0;
    cur = 0;
}

Vector::~Vector(void)
{
    if (beg != 0)
    {
        delete[] beg;
    }
    beg = 0;
}

Vector::Vector(int n)
{
    beg = new Object *[n];
    cur = 0;
    size = n;
}

void Vector::Add(Object *p)
{
    if (cur < size)
    {
        beg[cur] = p;
        ++cur;
    }
}

std::ostream &operator<<(std::ostream &out, const Vector &v)
{
    if (v.size == 0)
    {
        out << "Empty" << std::endl;
    }
    Object **obj = v.beg;
    for (int i = 0; i < v.cur; i++)
    {
        (*obj)->Show();
        ++obj;
    }
    return out;
}
