// 11. Составить программу для вычисления n-го числа Фибоначчи.

#include <iostream>

unsigned int fibonacci(unsigned int i)
{
    if (i == 0)
    {
        return 0;
    }
    if (i <= 2)
    {
        return 1;
    }
    return fibonacci(i - 1) + fibonacci(i - 2);
}

int main()
{
    int n;
    std::cin >> n;
    if (n < 0)
    {
        std::cout << "Отриц. числа не принимаются" << '\n';
    }
    else
    {
        std::cout << fibonacci(n) << '\n';
    }
    return 0;
}
