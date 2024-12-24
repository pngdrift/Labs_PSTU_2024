// Метод итерации
//
// f(x) = 0.1x^2 - x*ln(x)
// [1;2]
//
// r = 1.29...
// lambda = 1/1.29 = 0.77...


#include <cmath>
#include <iostream>

int main()
{
    double epsilon = 0.00001;
    double lambda = 0.77;

    float x = 2;
    float xPrev = 0;
    while (std::abs(x - xPrev) > epsilon)
    {
        xPrev = x;
        x = lambda * (pow(0.1 * x, 2) - x * log(x)) + xPrev; // вычисляем Фи
    }
    std::cout << "Корень: " << x << "\n";
    return 0;
}
