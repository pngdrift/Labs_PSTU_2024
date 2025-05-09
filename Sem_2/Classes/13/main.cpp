/* 11 вариант
Задача 1
1. Контейнер - вектор
2. Тип элементов Money (см. лабораторную работу №3).
Задача 2
Адаптер контейнера - очередь.
Задача 3
Ассоциативный контейнер - словарь
 Задание 3
Найти среднее
арифметическое и
добавить его в начало
контейнера
 Задание 4
Найти элемент с
заданным ключом и
удалить их из контейнера
 Задание 5
Из каждого элемента вычесть
минимальный элемент
контейнера
 */

#include "Money.h"
#include <iostream>
#include <queue>
#include <vector>

typedef std::vector<Money> vc;

vc makeVector(int size)
{
    srand(time(0));
    vc v;
    for (int i = 1; i <= size; ++i)
    {
        Money tmp(rand() % 100, rand() % 100);
        v.push_back(tmp);
    }
    return v;
}

void printVector(vc v)
{
    int len = v.size();
    for (int i = 0; i < len; ++i)
    {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
}

int average(vc v)
{
    int sum = 0;
    int len = v.size();
    for (int i = 0; i < len; ++i)
    {
        sum += v[i].getRoubles() + v[i].getKopecks();
    }
    std::cout << "Average vec: " << sum / len << "\n";
    return sum / len;
}

void minElem(vc v)
{
    Money min = v[0];
    int len = v.size();
    for (int i = 0; i < len; ++i)
    {
        if (min > v[i])
        {
            min = v[i];
        }
    }
    std::cout << "Min elem " << min << "\n";
    for (int i = 0; i < len; ++i)
    {
        v[i] = v[i] - min;
    }
    printVector(v);
}

typedef std::queue<Money> q;

q makeQueue(int size)
{
    q queue;
    Money m;
    for (int i = 0; i < size; ++i)
    {
        std::cin >> m;
        queue.push(m);
    }
    return queue;
}

vc copyQueue(q queue)
{
    vc vector;
    while (!queue.empty())
    {
        vector.push_back(queue.front());
        queue.pop();
    }
    return vector;
}

q copyVector(vc v)
{
    q queue;
    int len = v.size();
    for (int i = 0; i < len; ++i)
    {
        queue.push(v[i]);
    }
    return queue;
}

void printQueue(q queue)
{
    std::cout << "Queue: ";
    while (!queue.empty())
    {
        std::cout << queue.front() << " ";
        queue.pop();
    }
    std::cout << '\n';
}

Money averageQ(q queue)
{
    vc vec = copyQueue(queue);
    int n = 1;
    Money sum = queue.front();
    queue.pop();
    while (!queue.empty())
    {
        sum = sum + queue.front();
        queue.pop();
        n++;
    }
    queue = copyVector(vec);
    std::cout << "Average queue: " << sum / n << '\n';
    return sum / n;
}

void addQueue(q &queue, Money m, int index)
{
    vc vec;
    Money mm;
    for (int i = 1; !queue.empty(); ++i)
    {
        mm = queue.front();
        if (i == index)
        {
            vec.push_back(m);
        }
        vec.push_back(mm);
        queue.pop();
    }
    queue = copyVector(vec);
}

Money minElem(q queue)
{
    Money min = queue.front();
    vc vec = copyQueue(queue);
    while (!queue.empty())
    {
        if (queue.front() < min)
        {
            min = queue.front();
        }
        queue.pop();
    }
    queue = copyVector(vec);
    std::cout << "Min elem: " << min << '\n';
    vc vec2;
    Money m;
    while (!queue.empty())
    {
        m = queue.front();
        vec2.push_back(m - min);
        queue.pop();
    }
    queue = copyVector(vec2);

    return min;
}

int main()
{
    std::vector<Money> mv;
    int size;
    std::cout << "Enter vector size: ";
    std::cin >> size;
    mv = makeVector(size);
    std::cout << "Vector (money): ";
    printVector(mv);

    Money a(average(mv), 0);
    mv.insert(mv.begin(), a);
    std::cout << "Result: ";
    printVector(mv);

    std::cout << "Vector - min Element\n";
    minElem(mv);

    Money money;
    q queue;
    std::cout << "Enter queue size: ";
    std::cin >> size;
    queue = makeQueue(size);
    printQueue(queue);
    averageQ(queue);
    int index;
    std::cout << "Index: ";
    std::cin >> index;
    addQueue(queue, money, index);
    std::cout << "Add elem: ";
    printQueue(queue);
    minElem(queue);
    std::cout << "Result: ";
    printQueue(queue);
    return 0;
}