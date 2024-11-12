#include <iostream>

int main()
{
    int a, b, action;
    std::cin >> a >> b >> action;
    switch (action)
    {
    case 1: {
        std::cout << a + b << '\n';
        break;
    }
    case 2: {
        std::cout << a - b << '\n';
        break;
    }
    case 3: {
        std::cout << a * b << '\n';
        break;
    }
    case 4: {
        if (b == 0)
        {
            std::cout << "Нелья делить на 0" << '\n';
        }
        else
        {
            std::cout << a / b << '\n';
        }
        break;
    }
    default:
        std::cout << "Неверный код операции" << '\n';
    }

    return 0;
}