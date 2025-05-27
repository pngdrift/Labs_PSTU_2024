#include <iostream>
#include <map>
typedef std::map<int, float> TMap;
typedef TMap::iterator it;

TMap makeMap(int n)
{
    TMap m;
    float a;
    for (int i = 0; i < n; i++)
    {
        std::cout << "?";
        std::cin >> a;
        m.insert(std::make_pair(i, a));
    }
    return m;
}

void printMap(TMap m)
{
    for (int i = 0; i < m.size(); i++)
    {
        std::cout << i << " : " << m[i] << " \n";
    }
}

int avg(TMap v)
{
    int s = 0;
    for (int i = 0; i < v.size(); i++)
    {
        s += v[i];
    }
    int n = v.size();
    return s / n;
}

int Max(TMap v)
{
    it i = v.begin();
    int nom = 0, k = 0;
    int m = (*i).second;
    while (i != v.end())
    {
        if (m < (*i).second)
        {
            m = (*i).second;
            nom = k;
        }
        i++;
        k++;
    }
    return nom;
}

int Min(TMap v)
{
    it i = v.begin();
    int nom = 0, k = 0;
    float m = (*i).second;
    while (i != v.end())
    {
        if (m > (*i).second)
        {
            m = (*i).second;
            nom = k;
        }
        i++;
        k++;
    }
    return nom;
}

void division(TMap &v)
{
    int m = v[Min(v)];
    for (int i = 0; i < v.size(); i++)
    {
        v[i] = v[i] / m;
    }
}

int main()
{
    int n;
    std::cout << "N?";
    std::cin >> n;
    TMap m = makeMap(n);
    printMap(m);
    
    int el = avg(m);
    std::cout << "avg=" << el << '\n';
    m.insert(std::make_pair(n, el));
    printMap(m);

    int imax = Max(m);
    std::cout << "max=" << m[imax] << " index=" << imax << '\n';
    m.erase(imax);
    printMap(m);

    int imin = Min(m);
    std::cout << "min=" << m[imin] << " index=" << imin << '\n';
    division(m);
    printMap(m);

    return 0;
}
