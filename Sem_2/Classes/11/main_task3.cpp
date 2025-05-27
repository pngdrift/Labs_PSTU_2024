#include "Money.cpp"
#include <iostream>
#include <vector>

template <class T> class Vector
{
    std::vector<T> v;
    int len;

  public:
    Vector()
    {
        len = 0;
    }
    Vector(int n);
    void Print();

    T Average();
    void AddToBegin(T el);
    int Max();
    void DelMin();
    void SubAverage();
};

template <class T> Vector<T>::Vector(int n)
{
    T a;
    for (int i = 0; i < n; i++)
    {
        std::cin >> a;
        v.push_back(a);
    }
    len = v.size();
}

template <class T> void Vector<T>::Print()
{
    for (int i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << " ";
    }
    std::cout << '\n';
}

template <class T> T Vector<T>::Average()
{
    T s = v[0];
    for (int i = 1; i < v.size(); i++)
    {
        s = s + v[i];
    }
    return s / v.size();
}

template <class T> void Vector<T>::AddToBegin(T el)
{
    v.insert(v.begin(), el);
}

template <class T> int Vector<T>::Max()
{
    T m = v[0];
    int n = 0;
    for (int i = 1; i < v.size(); i++)
    {
        if (v[i] > m)
        {
            m = v[i];
            n = i;
        }
    }
    return n;
}

template <class T> void Vector<T>::DelMin()
{
    T m = v[0];
    int n = 0;
    for (int i = 1; i < v.size(); i++)
    {
        if (v[i] < m)
        {
            m = v[i];
            n = i;
        }
    }
    v.erase(v.begin() + n);
}

template <class T> void Vector<T>::SubAverage()
{
    T sr = Average();
    for (int i = 0; i < v.size(); i++)
    {
        v[i] = v[i] + sr;
    }
}

int main()
{
    try
    {
        Vector<Money> v(3);
        v.Print();

        Money el = v.Average();
        v.AddToBegin(el);
        std::cout << "after add to begin:\n";
        v.Print();

        v.DelMin();
        std::cout << "after del min:\n";
        v.Print();

        v.SubAverage();
        std::cout << "after subverage:\n";
        v.Print();
    }
    catch (...)
    {
        std::cout << "error!";
    }
    return 0;
}