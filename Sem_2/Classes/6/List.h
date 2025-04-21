#pragma once
#include "Iterator.h"
#include <iostream>

class List
{
  public:
    List(int s, int k = 0);
    List(const List &a);
    ~List();
    List &operator=(const List &a);
    int &operator[](int index);
    List operator+(const int k);
    int operator()();

    friend std::ostream &operator<<(std::ostream &out, const List &a);
    friend std::istream &operator>>(std::istream &in, List &a);

    Iterator first();
    Iterator last();

  private:
    int size;
    int *data;
    Iterator begin;
    Iterator end;
};
