#include "List.h"
#include "error.h"
#include <iostream>

List::List()
{
    size = 0;
    beg = 0;
}

List::List(int l)
{
    if (l > MAX_SIZE)
    {
        throw error("List length more than MAXSIZE\n");
    }
    size = l;
    beg = new int[l];
    for (int i = 0; i < size; ++i)
    {
        beg[i] = 0;
    }
}

List::List(int l, int *arr)
{
    if (l > MAX_SIZE)
    {
        throw error("List length more than MAXSIZE\n");
    }
    size = l;
    beg = new int[size];
    for (int i = 0; i < size; ++i)
    {
        beg[i] = arr[i];
    }
}
List::List(const List &list)
{
    size = list.size;
    beg = new int[size];
    for (int i = 0; i < size; ++i)
    {
        beg[i] = list.beg[i];
    }
}

List::~List()
{
    if (beg != 0)
    {
        delete[] beg;
    }
}

List &List::operator=(const List &list)
{
    if (this == &list)
    {
        return *this;
    }
    if (beg != 0)
    {
        delete[] beg;
    }
    size = list.size;
    beg = new int[size];
    for (int i = 0; i < size; ++i)
    {
        beg[i] = list.beg[i];
    }
    return *this;
}

int List::operator[](int index)
{
    if (index > size)
    {
        throw error("index > size");
    }
    if (index < 0)
    {
        throw error("index < 0");
    }
    return beg[index];
}

List List::operator+(const List &other)
{
    List result;
    if (size != other.size)
    {
        return result;
    }
    result.size = size;
    result.beg = new int[size];
    for (int i = 0; i < size; ++i)
    {
        result.beg[i] = beg[i] + other.beg[i];
    }
    return result;
}

int List::operator-(int n)
{
    if (n >= 0 && n < size)
    {
        return beg[n];
    }
    else
    {
        throw error("Error n");
    }
}

std::ostream &operator<<(std::ostream &out, const List &list)
{
    if (list.size == 0)
    {
        out << "Empty" << '\n';
    }
    else
    {
        for (int i = 0; i < list.size; ++i)
        {
            out << list.beg[i] << " ";
        }
        out << '\n';
    }
    return out;
}

std::istream &operator>>(std::istream &in, List &list)
{
    for (int i = 0; i < list.size; ++i)
    {
        std::cout << " > ";
        in >> list.beg[i];
    }
    return in;
}
