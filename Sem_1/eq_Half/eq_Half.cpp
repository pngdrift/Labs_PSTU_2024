// Метод половинного деления
//
// f(x) = 0.1x^2 - x*ln(x)
// [1;2]

#include <cmath>
#include <iostream>

int main()
{
    double epsilon = 0.00001;

    float a = 1, b = 2;
    while ((b - a) > epsilon)
    {
        float c = (a + b) / 2;

        float fA = pow(0.1 * a, 2) - a * log(a);
        float fB = pow(0.1 * b, 2) - b * log(b);
        float fC = pow(0.1 * c, 2) - c * log(c);

        if ((fA * fC) < 0) // корень левее, сдвиг конца
        {
            b = c;
        }
        else if ((fC * fB) < 0) // корень правее, сдвиг начала
        {
            a = c;
        }
        else
        {
            std::cout << "what\n";
        }
    }
    std::cout << "Корни: " << a << "; " << b << '\n';
    return 0;
}
