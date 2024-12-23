// Метод Ньютона (Метод касательных)
//
// f(x) = 0.1x^2 - x*ln(x)
// [1;2]

#include <cmath>
#include <iostream>

int main()
{
    float epsilon = 0.00001;
    float x = 2;
    float xPrev = 0;
    while (std::abs(x - xPrev) > epsilon)
    {
        xPrev = x;
        // см. формулу нахождения Xi https://i.imgur.com/SiteQJd.png
        x = xPrev - ((pow(0.1 * xPrev, 2) - xPrev * log(xPrev)) / (-log(xPrev) + (xPrev/5) - 1));
    }
    std::cout << "Корень: " << x << "\n";
    return 0;
}