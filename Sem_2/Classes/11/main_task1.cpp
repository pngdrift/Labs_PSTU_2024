

#include <cstdlib>
#include <iostream>
#include <vector>

typedef std::vector<float> Vec;

Vec makeVector(int n)
{
    Vec v;
    for (int i = 0; i < n; ++i)
    {
        float a = rand() % 100 - 50;
        v.push_back(a);
    }
    return v;
}

void printVector(Vec v)
{
    for (int i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
}

float aveg(Vec v)
{
    float s = 0;

    for (int i = 0; i < v.size(); ++i)
    {
        s += v[i];
    }
    int n = v.size();
    return s / n;
}

void addVector(Vec &v, float el, int pos)
{
    v.insert(v.begin() + pos, el);
}

int max(Vec v)
{
    float m = v[0];
    int n = 0;
    for (int i = 0; i < v.size(); ++i)
    {
        if (m < v[i])
        {
            m = v[i];
            n = i;
        }
    }
    return n;
}

void delVector(Vec &v, int pos)
{
    v.erase(v.begin() + pos);
}

int min(Vec v)
{
    float m = v[0];
    int n = 0;
    for (int i = 0; i < v.size(); ++i)
        if (m > v[i])
        {
            m = v[i];
            n = i;
        }
    return n;
}

void divide(Vec &v)
{
    int m = min(v);
    for (int i = 0; i < v.size(); ++i)
    {
        v[i] = v[i] / v[m];
    }
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

        float el = aveg(v);

        std::cout << "pos?";
        int pos;
        std::cin >> pos;

        if (pos > v.size())
            throw 1;

        addVector(v, el, pos);

        printVector(v);

        int n_max = max(v);
        delVector(v, n_max);
        printVector(v);

        divide(v);
        printVector(v);
    }
    catch (int)
    {
        std::cout << "error!";
    }
}
