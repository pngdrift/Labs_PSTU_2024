#include "List.h"
#include <iostream>

List::List(int s, int k)
{
    size = s;
    data = new int[size];
    for (int i = 0; i < size; i++)
    {
        data[i] = k;
    }
    begin.elem = &data[0];
    end.elem = &data[size];
}

List::List(const List &a)
{
    size = a.size;
    data = new int[size];
    for (int i = 0; i < size; i++)
    {
        data[i] = a.data[i];
    }
    begin = a.begin;
    end = a.end;
}

List::~List()
{
    delete[] data;
    data = 0;
}

Iterator List::first()
{
    return begin;
}

Iterator List::last()
{
    return end;
}

List &List::operator=(const List &a)
{
    if (this == &a)
    {
        return *this;
    }
    if (data != 0)
    {
        delete[] data;
    }
    data = new int[size];
    for (int i = 0; i < size; i++)
    {
        data[i] = a.data[i];
    }
    begin = a.begin;
    end = a.end;
    return *this;
}

int &List::operator[](int index)
{
    if (index < size)
    {
        return data[index];
    }
    std::cout << "\nError! Index>size\n";
}

List List::operator+(const int k)
{
    List temp(size);
    for (int i = 0; i < size; i++)
    {
        temp.data[i] += data[i] + k;
    }
    return temp;
}

int List::operator()()
{
    return size;
}

std::ostream &operator<<(std::ostream &out, const List &a)
{
    std::cout << "List: ";
    for (int i = 0; i < a.size; ++i)
    {
        out << a.data[i] << " ";
    }
    return out;
}

std::istream &operator>>(std::istream &in, List &a)
{
    for (int i = 0; i < a.size; i++)
    {
        std::cout << i << " elem: ";
        in >> a.data[i];
    }
    return in;
}
