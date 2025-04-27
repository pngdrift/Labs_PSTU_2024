#include <iostream>

const int MAX_SIZE = 20;

class List
{
    int size, *beg;

  public:
    List();
    List(int l);
    List(int l, int *arr);
    List(const List &list);
    ~List();
    List &operator=(const List &list);
    int operator[](int index);
    List operator+(const List &other);
    int operator-(int n);

    friend std::ostream &operator<<(std::ostream &out, const List &list);
    friend std::istream &operator>>(std::istream &in, List &list);
};