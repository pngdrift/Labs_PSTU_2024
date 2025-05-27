#include "Money.cpp"
#include <algorithm>
#include <iostream>
#include <list>
#include <numeric>
// #include "../7/List.h"

template <class T> class Container
{
    std::list<T> lst;
    int len;

  public:
    Container() : len(0)
    {
    }
    Container(int n);
    void Print();
    T Avergae();
    void Add(T el);
    void Remove(T key);
    void SubtractMin();
};

template <class T> Container<T>::Container(int n)
{
    T a;
    for (int i = 0; i < n; i++)
    {
        std::cin >> a;
        lst.push_back(a);
    }
    len = lst.size();
}

template <class T> void Container<T>::Print()
{
    for (auto i = lst.begin(); i != lst.end(); i++)
    {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
}

template <class T> T Container<T>::Avergae()
{
    T sum = std::accumulate(lst.begin(), lst.end(), T());
    return sum / lst.size();
}

template <class T> void Container<T>::Add(T el)
{
    lst.push_front(el);
    len++;
}

template <class T> void Container<T>::Remove(T key)
{
    lst.remove(key);
    len = lst.size();
}

template <class T> void Container<T>::SubtractMin()
{
    if (lst.empty())
        return;
    T min_val = *min_element(lst.begin(), lst.end());
    for (auto i = lst.begin(); i != lst.end(); i++)
    {
        *i = *i - min_val;
    }
}

int main()
{
    int n;
    std::cout << "N?";
    std::cin >> n;

    Container<Money> c(n);
    c.Print();

    Money avg = c.Avergae();
    std::cout << "Avergae: " << avg << '\n';

    c.Add(avg);
    c.Print();

    Money key;
    std::cout << "Enter key to remove: ";
    std::cin >> key;
    c.Remove(key);
    c.Print();

    c.SubtractMin();
    c.Print();

    return 0;
}