#include "Money.cpp"
#include <iostream>
#include <map>

typedef std::map<int, Money> TMap;
typedef TMap::iterator it;

TMap makeMap(int n)
{
    TMap m;
    Money a;
    for (int i = 0; i < n; i++)
    {
        std::cin >> a;
        m.insert(std::make_pair(i, a));
    }
    return m;
}

void printMap(TMap m)
{
    for (auto i = m.begin(); i != m.end(); i++)
    {
        std::cout << i->first << " : " << i->second << '\n';
    }
}

Money aveg(TMap m)
{
    Money sum;
    for (auto i = m.begin(); i != m.end(); i++)
    {
        sum = sum + i->second;
    }
    return sum / m.size();
}

void addAvg(TMap &m, Money el)
{
    int new_key = m.begin()->first - 1;
    m.insert(std::make_pair(new_key, el));
}

void removeKey(TMap &m, int key)
{
    m.erase(key);
}

void subtractMin(TMap &m)
{
    if (m.empty())
    {
        return;
    }
    Money min_val = m.begin()->second;
    for (auto i = m.begin(); i != m.end(); i++)
    {
        i->second = i->second - min_val;
    }
}

int main()
{
    int n;
    std::cout << "N?";
    std::cin >> n;

    TMap m = makeMap(n);
    printMap(m);

    Money avg = aveg(m);
    std::cout << "Avergae: " << avg << "\n";

    addAvg(m, avg);
    printMap(m);

    int key;
    std::cout << "Enter key to remove: ";
    std::cin >> key;
    removeKey(m, key);
    printMap(m);

    subtractMin(m);
    printMap(m);

    return 0;
}
