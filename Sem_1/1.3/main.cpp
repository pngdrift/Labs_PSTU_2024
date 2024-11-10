#include <iostream>

int main()
{
    float a;
    std::cin >> a;
    if (a < 5)
    {
        a *= 3;
    }
    else if (a >= 5 && a <= 7)
    {
        a /= 10;
    }
    else
    {
        a += 3;
    }
    std::cout << a << '\n';
    
    return 0;
}