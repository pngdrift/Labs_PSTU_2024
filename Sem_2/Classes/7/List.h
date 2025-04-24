#include <iostream>
#include <ostream>
#pragma once

template <class T> class List
{
  private:
    int size;
    T *data;

  public:
    List(int size);
    ~List();
    int &operator()();
    List operator+(const List &other);
    T &operator[](int index);
    template <class U> friend std::ostream &operator<<(std::ostream &out, const List<U> &);
    template <class U> friend std::istream &operator>>(std::istream &in, List<U> &);
};

template <class T> std::ostream &operator<<(std::ostream &out, const List<T> &a)
{
    for (int i = 0; i < a.size; ++i)
    {
        out << a.data[i] << " ";
    }
    out << '\n';
    return out;
}

template <class T> std::istream &operator>>(std::istream &in, List<T> &a)
{
    for (int i = 0; i < a.size; i++)
    {
        std::cout << i << " elem: ";
        in >> a.data[i];
    }
    return in;
}

template <class T> List<T>::List(int size)
{
    this->size = size;
    data = new T[size];
}

template <class T> List<T>::~List()
{
}

template <class T> int &List<T>::operator()()
{
    return size;
}

template <class T> List<T> List<T>::operator+(const List &other)
{
    List<T> tmp(size);
    for (int i = 0; i < size; ++i)
    {
        tmp[i] = data[i] + other.data[i];
    }
    delete[] data;
    return tmp;
}

template <class T> T &List<T>::operator[](int index)
{
    if (index < size)
    {
        return data[index];
    }
    else
    {
        std::cout << "\nError index>size";
        return data[0];
    }
}
