#pragma once
#include <iostream>

class Iterator
{
  private:
    friend class List;
    int *elem;

  public:
    Iterator();
    void operator++();
    void operator--();
    int &operator*() const;
    bool operator!=(const Iterator &it);
};
