#include "Triad.h"
#include <iostream>

class Time : public Triad
{
  public:
    Time(void);
    ~Time(void);
    Time(int, int, int);
    Time(const Time &);

    int getHour();
    int getMinute();
    int getSec();

    void setHour(int);
    void setMinute(int);
    void setSec(int);

    void addMinute(int);
    void addSec(int);

    Time &operator=(const Time &);

    friend std::istream &operator>>(std::istream &in, Time &t);
    friend std::ostream &operator<<(std::ostream &out, const Time &t);

  protected:
    int hour, minute, second;
};