#include "Money.cpp"
#include <iostream>
#include <queue>
#include <vector>

typedef std::queue<Money> Que;
typedef std::vector<Money> Vec;

Que makeQueue(int n)
{
    Que q;
    Money m;
    for (int i = 0; i < n; i++)
    {
        std::cin >> m;
        q.push(m);
    }
    return q;
}

Vec copyQueueToVector(Que q)
{
    Vec v;
    while (!q.empty())
    {
        v.push_back(q.front());
        q.pop();
    }
    return v;
}

Que copyVectorToQueue(Vec v)
{
    Que q;
    for (int i = 0; i < v.size(); i++)
    {
        q.push(v[i]);
    }
    return q;
}

void printQueue(Que q)
{
    Vec v = copyQueueToVector(q);
    for (int i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << " ";
    }
    std::cout << '\n';
}

Money average(Que q)
{
    Vec v = copyQueueToVector(q);
    Money s = v[0];
    for (int i = 1; i < v.size(); i++)
        s = s + v[i];
    return s / v.size();
}

void addToBegin(Que &q, Money el)
{
    Vec v = copyQueueToVector(q);
    v.insert(v.begin(), el);
    q = copyVectorToQueue(v);
}

Money max(Que q)
{
    Vec v = copyQueueToVector(q);
    Money m = v[0];
    for (int i = 1; i < v.size(); i++)
    {
        if (v[i] > m)
        {
            m = v[i];
        }
    }
    return m;
}

void delMin(Que &q)
{
    Vec v = copyQueueToVector(q);
    Money m = v[0];
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
    q = copyVectorToQueue(v);
}

void subAverage(Que &q)
{
    Vec v = copyQueueToVector(q);
    Money a = average(q);
    for (int i = 0; i < v.size(); i++)
        v[i] = v[i] + a;
    q = copyVectorToQueue(v);
}

int main()
{
    try
    {
        Que q;
        int n;
        std::cout << "N? ";
        std::cin >> n;
        q = makeQueue(n);
        printQueue(q);

        Money el = average(q);
        addToBegin(q, el);
        std::cout << "after add begin:\n";
        printQueue(q);

        delMin(q);
        std::cout << "after del min:\n";
        printQueue(q);

        subAverage(q);
        std::cout << "after sub average:\n";
        printQueue(q);
    }
    catch (...)
    {
        std::cout << "error!";
    }
    return 0;
}