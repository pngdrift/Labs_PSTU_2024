#include <iostream>

int main()
{
    int a, b, c, max;
    std::cin >> a >> b >> c;
    max = a;
    if (b > max) 
    {
        max = b;
    }
    if (c > max)
    {
        max = c;
    }
    std::cout << max << '\n';
    
    return 0;
}