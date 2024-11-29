#include <cmath>
#include <iostream>

int main()
{
    float a, b, c;
    std::cout << "Введите a, b и c: ";
    std::cin >> a >> b >> c;
    float D = b * b - 4 * a * c;
    if (D >= 0)
    {
        float x1 = (-b + sqrt(D)) / (2 * a);
        float x2 = (-b - sqrt(D)) / (2 * a);
        std::cout << "X1 = " << x1 << '\n';
        std::cout << "X2 = " << x2 << '\n';
    }
    else
    {
        std::cout << "Нет решения" << '\n';
    }
    return 0;
}
