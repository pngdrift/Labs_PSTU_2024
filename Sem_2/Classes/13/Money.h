#pragma once
#include <ostream>
class Money
{
    long int roubles;
    int kopecks;

  public:
    Money();
    Money(long int, int);
    Money(const Money &m);

    long int getRoubles();
    int getKopecks();
    void setRoubles(long int);
    void setKopecks(int);

    friend std::ostream &operator<<(std::ostream &out, const Money &p);
    friend std::istream &operator>>(std::istream &in, Money &p);
    friend bool operator>(const Money &first, const Money &second);
    friend bool operator<(const Money &first, const Money &second);
    Money &operator=(const Money &);
    Money &operator++();
    Money operator++(int);
    Money operator+(const Money &);
    Money operator-(const Money &);
    Money operator/(const Money &);
    Money operator/(const int &);
};
