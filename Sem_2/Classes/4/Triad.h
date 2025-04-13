#pragma once
#include <iostream>

class Triad
{
  public:
    Triad(void);

    virtual ~Triad(void);
    Triad(int, int, int);
    Triad(const Triad &);

    int getFirst();
    int getSecond();
    int getThird();

    void setFirst(int);
    void setSecond(int);
    void setThird(int);

    Triad &operator=(const Triad &);

    friend std::istream &operator>>(std::istream &in, Triad &t);
    friend std::ostream &operator<<(std::ostream &out, const Triad &t);

  protected:
    int first;
    int second;
    int third;
};