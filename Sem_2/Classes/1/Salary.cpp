#include "Salary.h"
#include <iostream>

void Salary::Init(float f, unsigned int s)
{
    first = f;
    second = s;
}

void Salary::Show()
{
    std::cout << "\nfirst=" << first;
    std::cout << "\nsecond=" << second;
    std::cout << "\n";
}

void Salary::Read()
{
    std::cout << "\nоклад?";
    std::cin >> first;
    std::cout << "\nдни?";
    std::cin >> second;
}

float Salary::summa()
{
    return first / 31 * second;
}
