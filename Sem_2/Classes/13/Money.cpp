#include "Money.h"
#include <iostream>

Money::Money()
{
    roubles = kopecks = 0;
}

Money::Money(long int r, int k)
{
    roubles = r;
    kopecks = k;
}

Money::Money(const Money &m)
{
    roubles = m.roubles;
    kopecks = m.kopecks;
}

long int Money::getRoubles()
{
    return roubles;
}

int Money::getKopecks()
{
    return kopecks;
}

void Money::setRoubles(long int value)
{
    roubles = value;
}

void Money::setKopecks(int value)
{
    kopecks = value;
}

std::ostream &operator<<(std::ostream &out, const Money &p)
{
    out << "Money: ";
    out << p.roubles << "," << p.kopecks;
    out << '\n';
    return out;
}

std::istream &operator>>(std::istream &in, Money &m)
{
    long int r;
    int k;
    std::cout << "roubles?";
    in >> r;
    std::cout << "kopecks?";
    in >> k;
    m.setRoubles(r);
    m.setKopecks(k);
    return in;
}

bool operator>(const Money &first, const Money &second)
{
    if (first.roubles > second.roubles)
    {
        return true;
    }
    return first.kopecks > second.kopecks;
}

bool operator<(const Money &first, const Money &second)
{
    if (first.roubles < second.roubles)
    {
        return true;
    }
    return first.kopecks < second.kopecks;
}

Money &Money::operator=(const Money &m)
{
    if (&m == this)
    {
        return *this;
    }
    roubles = m.roubles;
    kopecks = m.kopecks;
    return *this;
}

Money &Money::operator++()
{
    ++kopecks;
    return *this;
}

Money Money::operator++(int)
{
    Money m(roubles, kopecks);
    kopecks++;
    return m;
}

Money Money::operator+(const Money &m)
{
    Money result;
    result.roubles = m.roubles + roubles;
    result.kopecks = m.kopecks + kopecks;
    return result;
}

Money Money::operator-(const Money &a)
{
    Money result;
    result.roubles = roubles - a.roubles;
    result.kopecks = kopecks - a.kopecks;
    return result;
}

Money Money::operator/(const Money &m)
{
    int temp1 = roubles * 100 + kopecks;
    int temp2 = m.roubles * 100 + m.kopecks;
    Money result;
    result.roubles = (temp1 + temp2) / 100;
    result.kopecks = (temp1 + temp2) % 100;
    return result;
}

Money Money::operator/(const int &i)
{
    Money result;
    result.roubles = roubles / i;
    result.kopecks = kopecks / i;
    return result;
}
