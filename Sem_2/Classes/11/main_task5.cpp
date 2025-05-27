#include "Money.cpp"
#include <iostream>
#include <queue>

template <class T> class Vector
{
    std::queue<T> q;
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
    T Max();
    void DelMin();
    void SubAverage();
};

template <class T> Vector<T>::Vector(int n)
{
    T a;
    for (int i = 0; i < n; i++)
    {
        std::cin >> a;
        q.push(a);
    }
    len = n;
}

template <class T> void Vector<T>::Print()
{
    std::queue<T> temp = q;
    while (!temp.empty())
    {
        std::cout << temp.front() << " ";
        temp.pop();
    }
    std::cout << '\n';
}

template <class T> T Vector<T>::Average()
{
    std::queue<T> temp = q;
    T s = temp.front();
    temp.pop();
    int count = 1;
    while (!temp.empty())
    {
        s = s + temp.front();
        temp.pop();
        count++;
    }
    return s / count;
}

template <class T> void Vector<T>::AddToBegin(T el)
{
    std::queue<T> temp;
    temp.push(el);
    while (!q.empty())
    {
        temp.push(q.front());
        q.pop();
    }
    q = temp;
}

template <class T> T Vector<T>::Max()
{
    std::queue<T> temp = q;
    T m = temp.front();
    temp.pop();
    while (!temp.empty())
    {
        if (temp.front() > m)
        {
            m = temp.front();
        }
        temp.pop();
    }
    return m;
}

template <class T> void Vector<T>::DelMin()
{
    std::queue<T> temp;
    T m = q.front();
    std::queue<T> t = q;
    while (!t.empty())
    {
        if (t.front() < m)
        {
            m = t.front();
        }
        t.pop();
    }

    bool deleted = false;
    while (!q.empty())
    {
        if (q.front() == m && !deleted)
        {
            q.pop();
            deleted = true;
        }
        else
        {
            temp.push(q.front());
            q.pop();
        }
    }
    q = temp;
}

template <class T> void Vector<T>::SubAverage()
{
    T sr = Average();
    std::queue<T> temp;
    while (!q.empty())
    {
        temp.push(q.front() + sr);
        q.pop();
    }
    q = temp;
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
        std::cout << "after sub average:\n";
        v.Print();
    }
    catch (...)
    {
        std::cout << "error!";
    }
    return 0;
}