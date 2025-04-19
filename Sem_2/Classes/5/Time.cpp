#include "Time.h"
#include <iostream>

Time::Time(void) : Triad()
{
}

Time::~Time(void)
{
}

Time::Time(int h, int m, int s)
{
    first = h;
    second = m;
    third = s;
}

Time::Time(const Time &time)
{
    first = time.first;
    second = time.second;
    third = time.third;
}

int Time::getHour()
{
    return first;
}

int Time::getMinute()
{
    return second;
}

int Time::getSec()
{
    return third;
}

void Time::setHour(int value)
{
    first = value;
}

void Time::setMinute(int value)
{
    second = value;
}

void Time::setSec(int value)
{
    third = value;
}

void Time::addMinute(int value)
{
    second += value;
}

void Time::addSec(int value)
{
    third += value;
}

Time &Time::operator=(const Time &t)
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

std::istream &operator>>(std::istream &in, Time &t)
{
    std::cout << "hour?";
    in >> t.first;
    std::cout << "minute?";
    in >> t.second;
    std::cout << "sec?";
    in >> t.third;
    return in;
}

std::ostream &operator<<(std::ostream &out, const Time &time)
{
    out << "Time:\n";
    out << " hour: " << time.first << "\n";
    out << " minute: " << time.second << "\n";
    out << " sec: " << time.third << "\n";
    return out;
}

void Time::Show()
{
    std::cout << "Time:\n";
    std::cout << " hour: " << first << "\n";
    std::cout << " minute: " << second << "\n";
    std::cout << " sec: " << third << "\n";
}
