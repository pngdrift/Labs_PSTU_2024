#include "Money.cpp"
#include <cstdlib>
#include <iostream>
#include <vector>

typedef std::vector<Money> Vec;

Vec makeVector(int n)
{
    Vec v;
    for (int i = 0; i < n; i++)
    {
        int a = rand() % 100 - 50;
        v.push_back(Money(a, a));
    }
    return v;
}

void printVector(Vec v)
{
    for (int i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << " ";
    }
    std::cout << '\n';
}

Money aveg(Vec v)
{
    Money s;
    for (int i = 0; i < v.size(); i++)
    {
        s += v[i];
    }
    int n = v.size();
    return s / n;
}

void addVector(Vec &v, Money el, int pos)
{
    v.insert(v.begin() + pos, el);
}

int main()
{
    try
    {
        int n;
        std::cout << "N?";
        std::cin >> n;
        Vec v = makeVector(n);
        printVector(v);
        Money el = aveg(v);
        std::cout << "pos?";
        int pos;
        std::cin >> pos;
        if (pos > v.size())
        {
            throw 1;
        }
        addVector(v, el, pos);
        printVector(v);
    }
    catch (int)
    {
        std::cout << "error!";
    }
    return 0;
}