#include "Triad.h"
#include <iostream>

Triad::Triad(void)
{
    first = second = third = 0;
}
Triad::~Triad(void)
{
}

Triad::Triad(int f, int s, int t)
{
    first = f;
    second = s;
    third = t;
}

Triad::Triad(const Triad &triad)
{
    first = triad.first;
    second = triad.second;
    third = triad.third;
}

int Triad::getFirst()
{
    return first;
}

int Triad::getSecond()
{
    return second;
}

int Triad::getThird()
{
    return third;
}

void Triad::setFirst(int value)
{
    first = value;
}

void Triad::setSecond(int value)
{
    second = value;
}

void Triad::setThird(int value)
{
    third = value;
}

Triad &Triad::operator=(const Triad &t)
{
    if (&t == this)
    {
        return *this;
    }
    first = t.first;
    second = t.second;
    third = t.third;
    return *this;
}

std::istream &operator>>(std::istream &in, Triad &t)
{
    std::cout << "first?";
    in >> t.first;
    std::cout << "second?";
    in >> t.second;
    std::cout << "third?";
    in >> t.third;
    return in;
}

std::ostream &operator<<(std::ostream &out, const Triad &t)
{
    out << "Triad:\n";
    out << " first: " << t.first << '\n';
    out << " second: " << t.second << '\n';
    out << " third: " << t.third << '\n';
    return out;
}