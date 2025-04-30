#pragma once
#include "Money.h"
#include <fstream>
#include <iostream>
#include <string>

int make_file(const char *f_name)
{
    std::fstream file(f_name, std::ios::out | std::ios::trunc);
    if (!file)
    {
        return -1;
    }
    int n;
    Money money;
    std::cout << "N?: ";
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        std::cin >> money;
        file << money << "\n";
    }
    file.close();
    return n;
}

int print_file(const char *fileName)
{
    std::fstream file(fileName, std::ios::in);
    if (!file)
    {
        return -1;
    }
    Money m;
    int i = 0;
    while (file >> m)
    {
        std::cout << m << "\n";
        i++;
    }
    file.close();
    return i;
}

int del_file(const char *fileName, int k)
{
    std::fstream temp("temp", std::ios::out);
    std::fstream file(fileName, std::ios::in);
    if (!file)
    {
        return -1;
    }
    int i = 0;
    Money m;
    while (file >> m)
    {
        if (file.eof())
        {
            break;
        }
        i++;
        if (i != k)
        {
            temp << m;
        }
    }
    file.close();
    temp.close();
    remove(fileName);
    rename("temp", fileName);
    return i;
}

int add_file(const char *fileName, int k, Money mm)
{
    std::fstream temp("temp", std::ios::out);
    std::fstream file(fileName, std::ios::in);
    if (!file)
    {
        return -1;
    }
    Money m;
    int i = 0, l = 0;
    while (file >> m)
    {
        if (file.eof())
        {
            break;
        }
        i++;
        if (i == k)
        {
            temp << m;
            l++;
        }
        temp << m;
    }
    file.close();
    temp.close();
    remove(fileName);
    rename("temp", fileName);
    return l;
}

int add_end(const char *f_name, Money m)
{
    std::fstream file(f_name, std::ios::app);
    if (!file)
    {
        return -1;
    }
    file << m;
    return 1;
}

int change_file(const char *f_name, Money mm, int k)
{
    std::fstream temp("temp", std::ios::out);
    std::fstream file(f_name, std::ios::in);
    if (!file)
    {
        return -1;
    }
    Money m;
    int i = 0, l = 0;
    char x;
    while (file >> m)
    {
        if (file.eof())
        {
            break;
        }
        i++;
        if (i == k)
        {
            std::cout << m << " - is changing... Continue[y/n]?\n";
            std::cin >> x;
            if (x == 'n' || x == 'N')
                break;
            temp << mm;
            l++;
        }
        else
            temp << m;
    }
    file.close();
    temp.close();
    remove(f_name);
    rename("temp", f_name);
    return l;
}
